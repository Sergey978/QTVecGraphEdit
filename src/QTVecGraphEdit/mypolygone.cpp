#include "MyPolygone.h"

#include <qmath.h>
#include <QPen>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>


MyPolygone::MyPolygone(const QPolygonF &pol, QGraphicsItem *parent):  QGraphicsPolygonItem (parent)
{

   setPolygon(pol);

    myColor = Qt::black;
    setPen(QPen(myColor, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));


}

QRectF MyPolygone::boundingRect() const
{

    QRectF  boundingRect= polygon().boundingRect();


    return boundingRect
            .normalized()
            .adjusted(-extra, -extra, extra, extra);


}

QPainterPath MyPolygone::shape() const
{
    QPainterPath path = QGraphicsPolygonItem::shape();
    return path;
}

void MyPolygone::setColor(const QColor &color)
{

}

void MyPolygone::updatePosition()
{

}

QPointF MyPolygone::getCenter() const
{
    int centerX = 0, centerY = 0, countP =0;
    foreach(QPointF point, polygon())
    {

        centerX += point.x();
        centerY += point.y();
        countP++;
    }

    return QPointF(centerX / countP, centerY /countP );
}

void MyPolygone::bindedScale(float scaleFactorX, float scaleFactorY)
{

    QPolygonF qpf = polygon();
    QPointF oldCenter  = getCenter();
    QTransform trans;
    trans=trans.scale(scaleFactorX,scaleFactorY);
    QPolygonF newPolygon(trans.map(qpf));
   setPolygon( newPolygon);
    QPointF newCenter  = getCenter();

    trans = trans.fromTranslate(oldCenter.x()- newCenter.x(), oldCenter.y() - newCenter.y());
    qpf = polygon();
    newPolygon = trans.map(qpf);
    setPolygon(newPolygon);



}




void MyPolygone::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    QPen myPen = pen();
    myPen.setColor(myColor);
    painter->setPen(myPen);
    painter->drawPolygon(polygon());

    if (isSelected())
    {
        // sets brush for end points
        painter->setBrush(Qt::SolidPattern);
        myPen.setColor(Qt::green);
        painter->setPen(myPen);
        foreach(QPointF point, polygon())
            {

                painter->drawEllipse(point, SELECT_POINT, SELECT_POINT);
            }

    }

}

void MyPolygone::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    offset = event->pos();

    // choise point for selecting
    int i =0;
    foreach(QPointF point, polygon())
        {

            if (getDistance(offset,mapToParent(point)) <=   SELECT_POINT + 3 )
            {
                _selectedPoint = i;
                _isResizing = true;
                return;
            }
            i++;
        }


 setSelected(true);
}

void MyPolygone::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{


    QPointF pos = event->pos() ;
    if (_isResizing)
    {

        prepareGeometryChange();
        polygon()[_selectedPoint] = pos;
    }
    else
    {



    }
 setPos(mapToParent(pos - offset));
}

void MyPolygone::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

}

int MyPolygone::getDistance(QPointF p1, QPointF p2)
{
     return   sqrt(pow(p1.x()- p2.x(), 2) + pow(p1.y()-p2.y(), 2));
}

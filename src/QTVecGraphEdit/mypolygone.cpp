#include "mypolygone.h"

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
    setSelected(true);
    offset = event->pos();

    // choise point for selecting

    for ( int i = 0 ; i <  polygon().length(); i++)
    {

        if (getDistance(offset,polygon()[i]) <=   SELECT_POINT )
        {

            _selectedPoint = i;
            _isResizing = true;

            return;
        }

        if (i > 0){
            if (getDistanceToLine(offset, polygon()[i], polygon()[i - 1]) <=   SELECT_POINT )
            {

                insertPoint(i, offset);
                _isResizing = false;
                return;

            }
        }
    }
    if (getDistanceToLine(offset, polygon().first(), polygon().last())  <=   SELECT_POINT){
        insertPoint(polygon().length(), offset);
    }

    _isResizing = false;

}

void MyPolygone::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{


    QPointF pos = event->pos() ;
    if (_isResizing)
    {
        prepareGeometryChange();

        QPolygonF qpf = polygon();
        qpf[_selectedPoint] = pos;
        setPolygon( qpf);
    }
    else
    {

        setPos(mapToParent(pos - offset));

    }

}

void MyPolygone::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

}

void MyPolygone::insertPoint(int pos, QPointF &point)
{
    QPolygonF qpf = polygon();
    qpf.insert(pos, point);
    setPolygon(qpf);
}
// pl1 and pl2 - points of line , p -point near the line
int MyPolygone::getDistanceToLine(QPointF p, QPointF pl1, QPointF pl2) const
{
    return abs((pl2.y() - pl1.y())*p.x() - (pl2.x() - pl1.x()) * p.y() + pl2.x() * pl1.y() - pl2.y() * pl1.x() )
            /
            sqrt(  pow(pl2.y() - pl1.y(), 2)  +  pow(pl2.x() -  pl1.x(), 2) );
}

int MyPolygone::getDistance(QPointF p1, QPointF p2) const
{
    return   sqrt(pow(p1.x()- p2.x(), 2) + pow(p1.y()-p2.y(), 2));
}

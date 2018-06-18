#include "myellypse.h"


#include <qmath.h>
#include <QPen>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>


MyEllypse::MyEllypse( QGraphicsItem *parent):QGraphicsEllipseItem( parent)
{

    myColor = Qt::black;
       setPen(QPen(myColor, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

}

QPointF MyEllypse::getCenter() const
{
    return center;
}

QRectF MyEllypse::boundingRect() const
{

    qreal extra = 5;
    // bounding rectangle for ellipse
    return QRectF(QPointF(center.x() - width / 2, center.y() - height / 2), QSizeF(width, height) )
            .normalized()
            .adjusted(-extra, -extra, extra, extra);
}

QPainterPath MyEllypse::shape() const
{

    QPainterPath path = QGraphicsEllipseItem::shape();

    return path;
}

void MyEllypse::setColor(const QColor &color) { myColor = color; }

void MyEllypse::updatePosition()
{

}

void MyEllypse::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{


    // draws/paints the path of line
    QPen myPen = pen();
    myPen.setColor(myColor);

    painter->setPen(myPen);
    painter->setBrush(myColor);

    painter->drawEllipse(QPointF(center.x() - width / 2, center.y() - height / 2), width, height);

    if (isSelected())
    {
        // sets brush for end points
        painter->setBrush(Qt::SolidPattern);
        myPen.setColor(Qt::green);
        painter->setPen(myPen);
        painter->drawEllipse(QPointF(center.x() - width / 2, center.y()), SELECT_POINT, SELECT_POINT);
        painter->drawEllipse(QPointF(center.x() + width / 2, center.y()), SELECT_POINT, SELECT_POINT);

    }

}

void MyEllypse::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
offset = event->pos();

if(event->button() == Qt::LeftButton) {


        if (getDistance(offset,mapToParent(QPointF(center.x() - width / 2,  center.y()))) <=   SELECT_POINT)
        {
            _selectedPoint = 1;
            _isResizing = true;
            qDebug() << "_selectedPoint = 1;  ";
        }
        else if (getDistance(offset,mapToParent(QPointF(center.x() + width / 2,  center.y()))) <=  SELECT_POINT)
        {
            _selectedPoint = 2;
            _isResizing = true;

        }
        else
            _isResizing = false;
        setSelected(true);
    }


}

void MyEllypse::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{

}

void MyEllypse::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

}

int MyEllypse::getDistance(QPointF p1, QPointF p2)
{
     return   sqrt(pow(p1.x()- p2.x(), 2) + pow(p1.y()-p2.y(), 2));
}

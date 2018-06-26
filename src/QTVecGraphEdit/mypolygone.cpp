#include "MyPolygone.h"



#include <qmath.h>
#include <QPen>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>



MyPolygone::MyPolygone(const QPointF &firstP, QGraphicsItem *parent):  QGraphicsPolygonItem (parent)
{
    qDebug()<< " 0";
points.append( firstP);

myColor = Qt::black;
setPen(QPen(myColor, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

qDebug()<< " 10";
}

QRectF MyPolygone::boundingRect() const
{
    int minX = 0, minY = 0;
    int maxX = 0, maxY = 0;

    for (int i = 0; i < points.length() ; i++)
    {
        qDebug()<< " 1";

        minX = points[i].x() < minX ?  points[i].x(): minX;
        maxX = points[i].x() > maxX ?  points[i].x(): maxX;
        minY = points[i].y() < minY ? points[i].y(): minY;
        maxY = points[i].y() > maxY ? points[i].y(): maxY;
        qDebug()<< " 2";
    }
 return QRectF(QPointF(minX, minY), QSize(maxX - minX, maxY - minY))
         .normalized()
         .adjusted(-extra, -extra, extra, extra);


}

QPainterPath MyPolygone::shape() const
{
        return path;
}

void MyPolygone::setColor(const QColor &color)
{

}

void MyPolygone::updatePosition()
{

}

void MyPolygone::addPoint(QPointF &point)
{
    points.append(point);
}

void MyPolygone::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    QPen myPen = pen();
    myPen.setColor(myColor);

    painter->setPen(myPen);

     painter->drawPolygon(QPolygonF(points));



}

void MyPolygone::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

}

void MyPolygone::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{

}

void MyPolygone::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

}

int MyPolygone::getDistance(QPointF p1, QPointF p2)
{

}

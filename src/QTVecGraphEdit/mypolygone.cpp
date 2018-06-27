#include "MyPolygone.h"



#include <qmath.h>
#include <QPen>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>



MyPolygone::MyPolygone(const QPointF &firstP, QGraphicsItem *parent):  QGraphicsPolygonItem (parent)
{

points.append( firstP);

myColor = Qt::black;
setPen(QPen(myColor, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));


}

QRectF MyPolygone::boundingRect() const
{
    int minX = points[0].x(), minY = points[0].y();
    int maxX = points[0].x(), maxY =points[0].y();

    for (int i = 0; i < points.length() ; i++)
    {
               minX = points[i].x() < minX ?  points[i].x(): minX;
        maxX = points[i].x() > maxX ?  points[i].x(): maxX;
        minY = points[i].y() < minY ? points[i].y(): minY;
        maxY = points[i].y() > maxY ? points[i].y(): maxY;

    }


 return QRectF(QPointF(minX, minY), QSize(maxX - minX, maxY - minY))
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

void MyPolygone::addPoint(QPointF &point)
{
    points.append(point);
}

void MyPolygone::setLastPoint(QPointF &point)
{
    qDebug() << "MyPolygone::setLastPoint";
    if (points.length() > 0){
        points[points.length() - 1] = point;
    }
    else
    {
        points.append(point);
    }

    update();
}

void MyPolygone::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
qDebug() << "draw polygone";

for (int i = 0; i < points.length() ; i++)
{
   qDebug()<< "points i " << i <<points[i];



}

    QPen myPen = pen();
    myPen.setColor(myColor);
    painter->setPen(myPen);
    painter->drawPolygon(QPolygonF(points));


    // test bounding rectangle

    int minX = points[0].x(), minY = points[0].y();
    int maxX = points[0].x(), maxY =points[0].y();


    for (int i = 0; i < points.length() ; i++)
    {
        minX = points[i].x() < minX ?  points[i].x(): minX;
        maxX = points[i].x() > maxX ?  points[i].x(): maxX;
        minY = points[i].y() < minY ? points[i].y(): minY;
        maxY = points[i].y() > maxY ? points[i].y(): maxY;

    }
 qDebug()<< "min i " <<minX <<   minY <<  maxX  << maxY;
    myPen.setColor("orange");
    painter->setPen(myPen);
    painter->drawRect(minX,minY,maxX - minX, maxY - minY);


}

void MyPolygone::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

}

void MyPolygone::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{

    updatePosition();
    QPointF pos = event->pos() ;
    if (_isResizing)
    {

    }
    else
    {

        updatePosition();

    }

}

void MyPolygone::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

}

int MyPolygone::getDistance(QPointF p1, QPointF p2)
{

}

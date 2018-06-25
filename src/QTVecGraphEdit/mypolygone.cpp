#include "MyPolygone.h"

MyPolygone::MyPolygone(QGraphicsItem *parent):  QGraphicsPolygonItem (parent)
{


}

QRectF MyPolygone::boundingRect() const
{
    int minX = 0, minY = 0;
    int maxX = 0, maxY = 0;

    for (int i = 0; i < points.length() ; i++)
    {

        minX = points[i]->x() < minX ?  points[i]->x(): minX;
        maxX = points[i]->x() > maxX ?  points[i]->x(): maxX;
        minY = points[i]->y() < minY ? points[i]->y(): minY;
        maxY = points[i]->y() > maxY ? points[i]->y(): maxY;

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

void MyPolygone::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
     path.moveTo(*points[0]);
     int length = points.length();

     if (length >= 1)
     {
         for (int i = 1; i < points.length() ; i++)
         {
            path.lineTo(*points[i]);


         }
     }
   path.lineTo(*points[0]);
    tempPolygon = path.toFillPolygon();
    setPolygon(tempPolygon);


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

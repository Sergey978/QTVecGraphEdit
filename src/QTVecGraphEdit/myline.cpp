#include "myline.h"

#include <qmath.h>
#include <QPen>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>


MyLine::MyLine(  QLineF line, QGraphicsItem *parent):QGraphicsLineItem(line, parent)
{

    myColor = Qt::black;
    setPen(QPen(myColor, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

}



QRectF MyLine::boundingRect() const
{
    qreal extra = 1.5;

    // bounding rectangle for line
    return QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(),
                                      line().p2().y() - line().p1().y()))
            .normalized()
            .adjusted(-extra, -extra, extra, extra);
}

QPainterPath MyLine::shape() const
{
    QPainterPath path = QGraphicsLineItem::shape();

    return path;
}

void MyLine::updatePosition()
{


}


void MyLine::paint(QPainter *painter, const QStyleOptionGraphicsItem *,
                   QWidget *)
{


    // from other project example
    // draws/paints the path of line
    QPen myPen = pen();
    myPen.setColor(myColor);

    painter->setPen(myPen);
    painter->setBrush(myColor);

    painter->drawLine(line());

    if (isSelected())
    {
        // sets brush for end points
        painter->setBrush(Qt::SolidPattern);
        myPen.setColor(Qt::green);
        painter->setPen(myPen);
        painter->drawEllipse(line().p1(), SELECT_POINT, SELECT_POINT);
        painter->drawEllipse(line().p2(), SELECT_POINT, SELECT_POINT);

    }


update();
}

void MyLine::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "MyLine::mousePressEvent  ";
    if(event->button() == Qt::LeftButton) {
        QPointF pos = event->scenePos();
        if (getDistance(pos, line().p1()) <=   SELECT_POINT)
        {
            _selectedPoint = 1;
            _isResizing = true;
             qDebug() << "_selectedPoint = 1;  ";
        }
        else if (getDistance(pos, line().p2()) <=  SELECT_POINT)
        {
            _selectedPoint = 2;
            _isResizing = true;
            qDebug() << "_selectedPoint = 2;  ";
        }
        else
            _isResizing = false;
        setSelected(true);
    }
}

void MyLine::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (_isResizing)
    {
    prepareGeometryChange();
        QPointF pos = event->scenePos();
        if (_selectedPoint ==1 )
        {
            QLineF tempLine = line();
            tempLine.setP1(pos);
            setLine(tempLine);

            qDebug() << "pos p1 x=  " << pos.x() <<  "pos p1 y=  " << pos.y();

        }
        else if(_selectedPoint == 2)
        {
            QLineF tempLine = line();
            tempLine.setP2(pos);
            setLine(tempLine);


            qDebug() << "pos p2 x=  " << pos.x() <<  "pos p2 y=  " << pos.y();
        }
    }
    else
    {
        QGraphicsItem::mouseMoveEvent(event);
    }
    update();
}

void MyLine::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

}

int MyLine::getDistance(QPointF p1, QPointF p2)
{
    qDebug() << " getDistance " << sqrt(pow(p1.x()- p2.x(), 2) + pow(p1.y()-p2.y(), 2));;
    return   sqrt(pow(p1.x()- p2.x(), 2) + pow(p1.y()-p2.y(), 2));
}





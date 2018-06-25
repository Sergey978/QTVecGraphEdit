#include "myellypse.h"


#include <qmath.h>
#include <QPen>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>


MyEllypse::MyEllypse(const QRectF & outline, QGraphicsItem *parent):QGraphicsEllipseItem( parent)
{

    center.setX(outline.x()+outline.width()/2);
    center.setY(outline.y() + outline.height()/2);
    width = outline.width();
    height = outline.height();
    myColor = Qt::black;
    setPen(QPen(myColor, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

}

QPointF MyEllypse::getCenterF() const
{
    int x =rect().x() + rect().width() /2;
    int y = rect().y() + rect().height() /2;
    return QPointF(x, y);
}

QRectF MyEllypse::boundingRect() const
{

    qreal extra = 8;
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

    center.setX(rect().x() + rect().width() / 2);
    center.setY(rect().y() + rect().height() / 2) ;
    width = rect().width() ;
    height = rect().height();
}

void MyEllypse::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{

    updatePosition();

    // draws/paints the path of ellipse
    QPen myPen = pen();
    myPen.setColor(myColor);

    painter->setPen(myPen);
    // painter->setBrush(myColor);

    painter->drawEllipse(rect());

    if (isSelected())
    {
        // sets brush for end points
        painter->setBrush(Qt::SolidPattern);
        myPen.setColor(Qt::green);
        painter->setPen(myPen);

        painter->drawEllipse(QPointF(center.x() - width / 2, center.y()), SELECT_POINT, SELECT_POINT);
        painter->drawEllipse(QPointF(center.x() + width / 2, center.y()), SELECT_POINT, SELECT_POINT);

        painter->drawEllipse(QPointF(center.x() , center.y() - height / 2), SELECT_POINT, SELECT_POINT);
        painter->drawEllipse(QPointF(center.x() , center.y() + height / 2), SELECT_POINT, SELECT_POINT);

        painter->drawRect(center.x() - width / 2, center.y()  - height / 2, SELECT_POINT + 3, SELECT_POINT  + 3);
        painter->drawRect(center.x() + width / 2, center.y()  - height / 2, SELECT_POINT  + 3, SELECT_POINT  + 3);

        painter->drawRect(center.x() - width / 2 , center.y() + height / 2, SELECT_POINT  + 3, SELECT_POINT  + 3);
        painter->drawRect(center.x() + width / 2, center.y() + height / 2, SELECT_POINT  + 3, SELECT_POINT  + 3);


    }

}

void MyEllypse::mousePressEvent( QGraphicsSceneMouseEvent *event)
{

    offset = event->pos();

    // choise point for selecting
    if(event->button() == Qt::LeftButton) {

        if (getDistance(offset,mapToParent(QPointF(center.x() - width / 2,  center.y()))) <=   SELECT_POINT + 3)
        {
            _selectedPoint = 1;
            _isResizing = true;
        }
        else if (getDistance(offset,mapToParent(QPointF(center.x() + width / 2,  center.y()))) <=  SELECT_POINT + 3)
        {
            _selectedPoint = 2;
            _isResizing = true;

        }
        else if (getDistance(offset,mapToParent(QPointF(center.x() ,  center.y() + height / 2))) <=  SELECT_POINT + 3)
        {
            _selectedPoint = 3;
            _isResizing = true;

        }
        else if (getDistance(offset,mapToParent(QPointF(center.x(),  center.y() -  height / 2))) <=  SELECT_POINT + 3)
        {
            _selectedPoint = 4;
            _isResizing = true;

        }

        else
            _isResizing = false;
        setSelected(true);
    }


}

void MyEllypse::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{

    updatePosition();
    QPointF pos = event->pos() ;
    if (_isResizing)
    {
        prepareGeometryChange();

        if (_selectedPoint ==1  || _selectedPoint == 2)
        {

            double dx = abs(pos.x()- center.x());

            setRect(center.x() - dx, center.y() - height / 2, dx *2, height);

        }
        else if(_selectedPoint == 3 || _selectedPoint == 4 )
        {
            double dy = abs(pos.y() - center.y());

            setRect(center.x() - width /2 , center.y() - dy  , width , dy * 2);



        }
    }
    else
    {
        setRect(pos.x() - width /2, pos.y() - height /2, width, height);
        updatePosition();

    }


}

void MyEllypse::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

}

int MyEllypse::getDistance(QPointF p1, QPointF p2)
{
    return   sqrt(pow(p1.x()- p2.x(), 2) + pow(p1.y()-p2.y(), 2));
}

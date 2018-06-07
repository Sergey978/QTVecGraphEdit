#include "myline.h"

#include <qmath.h>
#include <QPen>
#include <QPainter>


MyLine::MyLine(  QLineF &line, QGraphicsItem *parent):QGraphicsLineItem(parent)
{

    myColor = Qt::black;
    setPen(QPen(myColor, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
}



QRectF MyLine::boundingRect() const
{
    qreal extra = 1.0;

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
   // QLineF line(mapFromItem(myStartItem, 0, 0), mapFromItem(myEndItem, 0, 0));
  //  setLine(line);
}


void MyLine::paint(QPainter *painter, const QStyleOptionGraphicsItem *,
          QWidget *)
{


    QPen myPen = pen();
    myPen.setColor(myColor);

    painter->setPen(myPen);
    painter->setBrush(myColor);
//! [4] //! [5]


//! [6] //! [7]
    painter->drawLine(line());

    if (isSelected()) {
        painter->setPen(QPen(myColor, 1, Qt::DashLine));
        QLineF myLine = line();
        myLine.translate(0, 4.0);
        painter->drawLine(myLine);
        myLine.translate(0,-8.0);
        painter->drawLine(myLine);
    }
}





// from other project example

/*
void MyLine::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                  QWidget *widget)
{
    // draws/paints the path of line
    QPen paintpen;
    painter->setRenderHint(QPainter::Antialiasing);
    paintpen.setWidth(1);

    if (isSelected())
    {
        // sets brush for end points
        painter->setBrush(Qt::SolidPattern);
        paintpen.setColor(Qt::red);
        painter->setPen(paintpen);
        painter->drawEllipse(start_p, 2, 2);
        painter->drawEllipse(end_p, 2, 2);

        // sets pen for line path
        paintpen.setStyle(Qt::DashLine);
        paintpen.setColor(Qt::black);
        painter->setPen(paintpen);
        painter->drawLine(start_p, end_p);
    }
    else
    {   painter->save();
        painter->setBrush(Qt::SolidPattern);
        paintpen.setColor(Qt::black);
        painter->setPen(paintpen);
        painter->drawEllipse(start_p, 2, 2);
        painter->drawEllipse(end_p, 2, 2);
        painter->drawLine(start_p, end_p);
        painter->restore();
    }
}
*/

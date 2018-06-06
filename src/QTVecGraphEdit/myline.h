#ifndef MYLINE_H
#define MYLINE_H

#include <QGraphicsLineItem>


QT_BEGIN_NAMESPACE
class QGraphicsPolygonItem;
class QGraphicsLineItem;
class QGraphicsScene;
class QRectF;
class QGraphicsSceneMouseEvent;
class QPainterPath;
QT_END_NAMESPACE

class MyLine :  public QGraphicsLineItem
{
    Q_OBJECT
public:
    MyLine(QGraphicsItem *parent = 0);

        QRectF boundingRect() const override;
        QPainterPath shape() const override;
        void setColor(const QColor &color) { myColor = color; }
        void updatePosition();


protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) override;

private:

    QColor myColor;

};

#endif // MYLINE_H

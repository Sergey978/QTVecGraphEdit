#ifndef MYELLYPSE_H
#define MYELLYPSE_H

#include <QGraphicsEllipseItem>


class MyEllypse: public QGraphicsEllipseItem
{
public:
     static const int SELECT_POINT = 5;

    MyEllypse(  QGraphicsItem *parent = 0);

    QPointF getCenter() const;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void setColor(const QColor &color);
    void updatePosition();
    qreal extra = 5;

    int type() const
       {
           // Enable the use of qgraphicsitem_cast with this item.
           return UserType+2;
       }

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:


    QColor myColor;
    bool _isResizing;
    int _selectedPoint;
    QPointF offset;
    QPoint center;
    float width;
    float height;


    int getDistance(QPointF p1, QPointF p2) ;


};






#endif // MYELLYPSE_H

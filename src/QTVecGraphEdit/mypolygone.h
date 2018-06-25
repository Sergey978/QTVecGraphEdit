#ifndef MYPOLYGONE_H
#define MYPOLYGONE_H

#include <QList>
#include <QGraphicsPolygonItem>

class MyPolygone: public QGraphicsPolygonItem
{
public:
    static const int SELECT_POINT = 5;

    MyPolygone(QGraphicsItem *parent);

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void setColor(const QColor &color);
    void updatePosition();
    qreal extra = 8;

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
    QPainterPath path;
    QPolygonF tempPolygon;

    QList<QPointF *> points;

    int getDistance(QPointF p1, QPointF p2) ;


};

#endif // MYPOLYGONE_H

#ifndef MYPOLYGONE_H
#define MYPOLYGONE_H

#include <QList>
#include <QGraphicsPolygonItem>

class MyPolygone: public QGraphicsPolygonItem
{
public:
    static const int SELECT_POINT = 5;

    MyPolygone( const QPolygonF & pol, QGraphicsItem *parent = 0);

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void setColor(const QColor &color);
    void updatePosition();
    qreal extra = 8;

    int type() const
    {
        // Enable the use of qgraphicsitem_cast with this item.
        return UserType+25;
    }

    QPointF getCenter() const;
    void  bindedScale(float scaleFactorX, float scaleFactorY);

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

    void insertPoint(int pos, QPointF &point);

    int getDistance(QPointF p1, QPointF p2) const;
    int getDistanceToLine(QPointF p, QPointF pl1, QPointF pl2) const;


};

#endif // MYPOLYGONE_H

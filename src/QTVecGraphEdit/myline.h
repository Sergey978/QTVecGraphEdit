#ifndef MYLINE_H
#define MYLINE_H

#include <QGraphicsLineItem>


QT_BEGIN_NAMESPACE
class QGraphicsPolygonItem;
class QRectF;
class QPainterPath;
QT_END_NAMESPACE

class MyLine :  public QGraphicsLineItem
{

public:
    static const int SELECT_POINT = 3;

    MyLine( QLineF line, QGraphicsItem *parent = 0);
        QRectF boundingRect() const override;
        QPainterPath shape() const override;
        void setColor(const QColor &color) { myColor = color; }
        void updatePosition();


protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:

    int getDistance(QPointF p1, QPointF p2) ;
    QColor myColor;
    bool _isResizing;
    int _selectedPoint;

};

#endif // MYLINE_H

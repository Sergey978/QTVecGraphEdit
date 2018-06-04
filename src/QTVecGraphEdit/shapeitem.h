#ifndef SHAPEITEM_H
#define SHAPEITEM_H

#include<QGraphicsItem>

QT_BEGIN_NAMESPACE
class QPixmap;
class QGraphicsItem;
class QGraphicsScene;
class QWidget;
class QPolygonF;
QT_END_NAMESPACE


class ShapeItem : public QGraphicsItem
{
public:
    enum ShapeType { Line, Ellipse, Polygone};

    ShapeItem(ShapeType type, QMenu *contextMenu, QGraphicsItem *parent = 0);

    ShapeType getShapeType() const {return shapeType;}

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);


private:
    ShapeType shapeType;
    QMenu *myContextMenu;

};

#endif // SHAPEITEM_H

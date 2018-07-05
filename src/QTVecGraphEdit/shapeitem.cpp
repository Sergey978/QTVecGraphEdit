#include "shapeitem.h"

ShapeItem::ShapeItem(ShapeType type, QMenu *contextMenu , QGraphicsItem *parent)
{
    shapeType = type;
    myContextMenu = contextMenu;
    shape = parent;

    shape->setFlag(QGraphicsItem::ItemIsMovable, true);
    shape->setFlag(QGraphicsItem::ItemIsSelectable, true);
    shape->setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);

}

ShapeItem::ShapeItem(ShapeItem::ShapeType type, QGraphicsItem *parent)
{
    shapeType = type;
    myContextMenu = 0;
    shape = parent;

    shape->setFlag(QGraphicsItem::ItemIsMovable, true);
    shape->setFlag(QGraphicsItem::ItemIsSelectable, true);
    shape->setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);

}

QGraphicsItem *ShapeItem::getShape()
{
    return shape;
}

void ShapeItem::setShape(QGraphicsItem *item)
{
    shape = item;
}


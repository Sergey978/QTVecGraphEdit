#include "shapeitem.h"

ShapeItem::ShapeItem(ShapeType type, QMenu *contextMenu, QGraphicsItem *parent):QAbstractGraphicsShapeItem (parent)
{
    shapeType = type;
    myContextMenu = contextMenu;
}

void ShapeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}

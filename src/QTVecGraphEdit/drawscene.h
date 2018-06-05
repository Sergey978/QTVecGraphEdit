#ifndef DRAWSCENE_H
#define DRAWSCENE_H

#include "shapeitem.h"

#include <QGraphicsScene>

QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
class QMenu;
class QPointF;
class QGraphicsLineItem;

QT_END_NAMESPACE

class DrawScene : public QGraphicsScene
{
    Q_OBJECT
public:
    DrawScene(QMenu *itemMenu, QObject *parent = 0);

    enum Mode {InsertItem, InsertLine, InsertText, MoveItem, ResizeItem};

public slots:
    void setMode(Mode mode);
    void setItemType(ShapeItem::ShapeType type);


signals:
    void itemInserted(ShapeItem *item);
    void textInserted(QGraphicsTextItem *item);
    void itemSelected(QGraphicsItem *item);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:
    bool isItemChange(int type);
    ShapeItem::ShapeType itemType;
    Mode myMode;
    QMenu *myMenuItem;
    QGraphicsLineItem *line;


};

#endif // DRAWSCENE_H
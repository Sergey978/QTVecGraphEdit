#ifndef DRAWSCENE_H
#define DRAWSCENE_H

#include "shapeitem.h"

#include <QGraphicsScene>
#include "myline.h"
#include "myellypse.h"
#include "mypolygone.h"

QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
class QMenu;
class QPointF;
QT_END_NAMESPACE

class DrawScene : public QGraphicsScene
{
    Q_OBJECT
public:
    DrawScene(QMenu *itemMenu, QObject *parent = 0);

    enum Mode {InsertEllipse, InsertPolygone,  InsertLine, InsertText, MoveItem, ResizeItem};

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
    MyLine *line;
    MyEllypse *ellipse;
    MyPolygone *polygone;


};

#endif // DRAWSCENE_H

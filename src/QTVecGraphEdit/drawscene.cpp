#include "drawscene.h"
#include <QGraphicsSceneMouseEvent>

DrawScene::DrawScene(QMenu *itemMenu, QObject *parent):QGraphicsScene(parent)
{
 myMenuItem = itemMenu;
 myMode = MoveItem;
 itemType = ShapeItem::Line;
 line = 0;


}

void DrawScene::setMode(DrawScene::Mode mode)
{
 myMode = mode;
}

void DrawScene::setItemType(ShapeItem::ShapeType type)
{
   itemType = type;
}

void DrawScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() != Qt::LeftButton)
        return;

    ShapeItem *item;
    switch (myMode) {
    case InsertItem:
        item = new ShapeItem(itemType, myMenuItem);
        // item->setBrush(myItemColor);
        addItem(item);
        item->setPos(mouseEvent->scenePos());
        emit itemInserted(item);
        break;
        //! [6] //! [7]
    case InsertLine:

        line = new QGraphicsLineItem(QLineF(mouseEvent->scenePos(),
                                            mouseEvent->scenePos()));
        item = new ShapeItem(ShapeItem::Line, myMenuItem, line);

        // line->setPen(QPen(myLineColor, 2));
        //addItem(line);
        addItem(item);
        break;
        //! [7] //! [8]
    case InsertText:
        /*
               textItem = new DiagramTextItem();
               textItem->setFont(myFont);
               textItem->setTextInteractionFlags(Qt::TextEditorInteraction);
               textItem->setZValue(1000.0);
               connect(textItem, SIGNAL(lostFocus(DiagramTextItem*)),
                       this, SLOT(editorLostFocus(DiagramTextItem*)));
               connect(textItem, SIGNAL(selectedChange(QGraphicsItem*)),
                       this, SIGNAL(itemSelected(QGraphicsItem*)));
               addItem(textItem);
               textItem->setDefaultTextColor(myTextColor);
               textItem->setPos(mouseEvent->scenePos());
               emit textInserted(textItem);
               */
        //! [8] //! [9]
    default:
        ;
    }
    QGraphicsScene::mousePressEvent(mouseEvent);
}

void DrawScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (myMode == InsertLine && line != 0) {
        QLineF newLine(line->line().p1(), mouseEvent->scenePos());
        line->setLine(newLine);
    } else if (myMode == MoveItem) {
        QGraphicsScene::mouseMoveEvent(mouseEvent);
    }
}

void DrawScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    /*
    if (line != 0 && myMode == InsertLine) {
        QList<QGraphicsItem *> startItems = items(line->line().p1());
        if (startItems.count() && startItems.first() == line)
            startItems.removeFirst();
        QList<QGraphicsItem *> endItems = items(line->line().p2());
        if (endItems.count() && endItems.first() == line)
            endItems.removeFirst();

        removeItem(line);
        delete line;

        if (startItems.count() > 0 && endItems.count() > 0 &&
                    startItems.first()->type() == DiagramItem::Type &&
                    endItems.first()->type() == DiagramItem::Type &&
                    startItems.first() != endItems.first()) {
                    DiagramItem *startItem = qgraphicsitem_cast<DiagramItem *>(startItems.first());
                    DiagramItem *endItem = qgraphicsitem_cast<DiagramItem *>(endItems.first());

                }


    }
*/
    line = 0;

    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}


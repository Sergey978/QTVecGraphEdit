#include "drawscene.h"
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

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
    case InsertEllipse:

        break;
        //! [6] //! [7]
    case InsertLine:
        line = new MyLine( QLineF(mouseEvent->scenePos(),
                                                   mouseEvent->scenePos()));
                item = new ShapeItem(ShapeItem::Line, myMenuItem, line);

                // line->setPen(QPen(myLineColor, 2));
                //addItem(line);
                addItem(item->getShape());


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
    update();
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



    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}


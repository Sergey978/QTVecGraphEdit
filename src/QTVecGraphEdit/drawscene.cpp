#include "drawscene.h"
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include"stdlib.h"

DrawScene::DrawScene(QMenu *itemMenu, QObject *parent):QGraphicsScene(parent)
{
    myMenuItem = itemMenu;
    myMode = MoveItem;
    itemType = ShapeItem::Line;
    line = 0;
    ellipse = 0;


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
    QPointF pt = mouseEvent->scenePos();
    if (mouseEvent->button() != Qt::LeftButton)
        return;

    ShapeItem *item;
    switch (myMode) {
    case InsertEllipse:

        ellipse = new MyEllypse(QRectF(pt.x(), pt.y(), 1, 1));

        item  = new ShapeItem(ShapeItem::Ellipse, myMenuItem, ellipse);
        addItem(item->getShape());
        ellipse->setRect(QRectF(pt.x(), pt.y(), 20, 20));

        break;

    case InsertLine:
        line = new MyLine( QLineF(pt, pt));
        item = new ShapeItem(ShapeItem::Line, myMenuItem, line);

        // line->setPen(QPen(myLineColor, 2));
        //addItem(line);
        addItem(item->getShape());

        break;

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
 QPointF mousePos = mouseEvent->scenePos();

    if (myMode == InsertLine && line != 0) {
        QLineF newLine(line->line().p1(), mousePos);
        line->setLine(newLine);
    }
    else if (myMode == InsertEllipse && ellipse !=0){

        double dx = abs(mousePos.x()- ellipse->getCenterF().x());
        double dy = abs(mousePos.y() - ellipse->getCenterF().y());
        ellipse->setRect(ellipse->getCenterF().x()- dx, ellipse->getCenterF().y()- dy, dx * 2, dy * 2);
            }
    else if (myMode == MoveItem) {
        QGraphicsScene::mouseMoveEvent(mouseEvent);
    }

}

void DrawScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{



    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}


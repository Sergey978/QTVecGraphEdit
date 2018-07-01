#include "drawscene.h"
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include"stdlib.h"
#include <qmath.h>
#include"QPointF"

DrawScene::DrawScene(QMenu *itemMenu, QObject *parent):QGraphicsScene(parent)
{
    myMenuItem = itemMenu;
    myMode = MoveItem;
    itemType = ShapeItem::Line;
    line = 0;
    ellipse = 0;
    polygone = 0;


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


    if (mouseEvent->button() != Qt::LeftButton){

        return;
    }


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

    case InsertPolygone:
    {

        QVector<QPointF> vectorPoints;
        vectorPoints.append(QPointF(pt.x(), pt.y() + 5));
        vectorPoints.append(QPointF(pt.x() - 5, pt.y() - 5));
        vectorPoints.append(QPointF(pt.x() + 5, pt.y() - 5));

        polygone = new MyPolygone(QPolygonF(vectorPoints) );
        item  = new ShapeItem(ShapeItem::Polygone, myMenuItem, polygone);

        addItem(item->getShape());

        break;

    }


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

    else if (myMode == InsertPolygone && polygone != 0){

        QPointF center =  polygone->getCenter();

        double dx = 1 + (mousePos.x()- oldMousePos.x()) / 50;
        double dy = 1 + (mousePos.y() - oldMousePos.y()) / 50;
        polygone->bindedScale(dx , dy );
        polygone->update();
    }
    else if (myMode == MoveItem) {
        QGraphicsScene::mouseMoveEvent(mouseEvent);
    }
oldMousePos = mousePos;
}

void DrawScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{



    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}


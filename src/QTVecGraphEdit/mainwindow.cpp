#include "mainwindow.h"

#include "drawscene.h"
#include "shapeitem.h"

#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
}

MainWindow::~MainWindow()
{
    createActions();
    createMenus();

    scene = new DrawScene(itemMenu, this);
    scene->setSceneRect(QRectF(0, 0, 1000, 1000));

    connect(scene, SIGNAL(itemInserted(ShapeItem*)),
            this, SLOT(itemInserted(ShapeItem*)));


    connect(scene, SIGNAL(itemSelected(QGraphicsItem*)),
            this, SLOT(itemSelected(QGraphicsItem*)));

    createToolbars();

    QHBoxLayout *layout = new QHBoxLayout;

    view = new QGraphicsView(scene);
    layout->addWidget(view);

    QWidget *widget = new QWidget;
    widget->setLayout(layout);

    setCentralWidget(widget);
    setWindowTitle(tr("Draw scene"));
    setUnifiedTitleAndToolBarOnMac(true);



}

void MainWindow::buttonGroupClicked(int id)
{

}

void MainWindow::itemInserted(ShapeItem *item)
{

}

void MainWindow::pointerGroupClicked(int id)
{

}

void MainWindow::itemSelected(QGraphicsItem *item)
{

}

void MainWindow::deleteItem()
{

}

void MainWindow::about()
{

}

void MainWindow::createActions()
{

}

void MainWindow::createMenus()
{

}

void MainWindow::createToolbars()
{

}

#include "mainwindow.h"

#include "drawscene.h"
#include "shapeitem.h"

#include <QtWidgets>

MainWindow::MainWindow()
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

MainWindow::~MainWindow()
{

}

void MainWindow::buttonGroupClicked(int id)
{

}

void MainWindow::itemInserted(ShapeItem *item)
{

}

void MainWindow::pointerGroupClicked(int id)
{
        scene->setMode(DrawScene::Mode(pointerTypeGroup->checkedId()));
}

void MainWindow::itemSelected(QGraphicsItem *item)
{

}

void MainWindow::deleteItem()
{

}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About Graph Editor"),
                       tr("The <b>Graph Editor</b> is simple  training project "
                          "use of the graphics framework."));
}

void MainWindow::createActions()
{
    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcuts(QKeySequence::Quit);
    exitAction->setStatusTip(tr("Quit Scenediagram example"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));


    deleteAction = new QAction(QIcon(":/Images/delete.png"), tr("&Delete"), this);
    deleteAction->setShortcut(tr("Delete"));
    deleteAction->setStatusTip(tr("Delete item from diagram"));
    connect(deleteAction, SIGNAL(triggered()), this, SLOT(deleteItem()));


    aboutAction = new QAction(tr("A&bout"), this);
    aboutAction->setShortcut(tr("Ctrl+B"));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(exitAction);

    itemMenu = menuBar()->addMenu(tr("&Item"));
    itemMenu->addAction(deleteAction);

    aboutMenu = menuBar()->addMenu(tr("&Help"));
    aboutMenu->addAction(aboutAction);
}

void MainWindow::createToolbars()
{

    editToolBar = addToolBar(tr("Edit"));
    editToolBar->addAction(deleteAction);


    QToolButton *pointerButton = new QToolButton;
    pointerButton->setCheckable(true);
    pointerButton->setChecked(true);
    pointerButton->setIcon(QIcon(":/Images/pointer.png"));

    QToolButton *linePointerButton = new QToolButton;
    linePointerButton->setCheckable(true);
    linePointerButton->setIcon(QIcon(":/Images/linepointer.png"));

    QToolButton *ellipsePointerButton = new QToolButton;
    ellipsePointerButton->setCheckable(true);
    ellipsePointerButton->setIcon(QIcon(":/Images/ellipse.png"));

    pointerTypeGroup = new QButtonGroup(this);
    pointerTypeGroup->addButton(pointerButton, int(DrawScene::MoveItem));
    pointerTypeGroup->addButton(linePointerButton, int(DrawScene::InsertLine));
    pointerTypeGroup->addButton(ellipsePointerButton, int(DrawScene::InsertEllipse));

    connect(pointerTypeGroup, SIGNAL(buttonClicked(int)),
            this, SLOT(pointerGroupClicked(int)));

    pointerToolbar = addToolBar(tr("Pointer type"));
    pointerToolbar->addWidget(pointerButton);
    pointerToolbar->addWidget(linePointerButton);
     pointerToolbar->addWidget(ellipsePointerButton);

}

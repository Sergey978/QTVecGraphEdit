#include "mainwindow.h"

#include "drawscene.h"
#include "shapeitem.h"
#include "svgreader.h"

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



    foreach (QGraphicsItem *item, scene->selectedItems()) {

        scene->removeItem(item);
        delete item;
    }


}

void MainWindow::saveToFile()
{
    QString filter;
    filter.append("SVG (*.svg)");
    filter += ";;AllFiles (*.*)";
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save"), "",
                                                   filter);



    if (fileName.isEmpty())
        return;
    else {
        if (!fileName.endsWith(".svg"))
            fileName += ".svg";

        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::information(this, tr("Unable to open file"),
                                     file.errorString());
            return;
        }



        QSvgGenerator generator;      // Create a file generator object
        generator.setFileName(fileName);    // We set the path to the file where to save vector graphics
        generator.setSize(QSize(scene->width(), scene->height()));  // Set the dimensions of the working area of the document in millimeters
        generator.setViewBox(QRect(0, 0, scene->width(), scene->height())); // Set the work area in the coordinates
        generator.setTitle(trUtf8("SVG Draw Scene"));                          // The title document
        generator.setDescription(trUtf8("File created by Vec Editor"));

        QPainter painter;
            painter.begin(&generator);
            scene->render(&painter);
            painter.end();

    }
}

void MainWindow::loadFromfile()
{
    QString fileName = QFileDialog::getOpenFileName(this,
            tr("Open"), "",
            tr("SVG files (*.svg);;All Files (*)"));


    if (fileName.isEmpty())
            return;
        else {

            QFile file(fileName);

            if (!file.open(QIODevice::ReadOnly)) {
                QMessageBox::information(this, tr("Unable to open file"),
                    file.errorString());
                return;
            }

    }

       scene->clear();
       // set dimensions graphics scene
       scene->setSceneRect(SvgReader::getSizes(fileName));

       //set on graphics scene objects

       foreach (ShapeItem *newItem, SvgReader::getElements(fileName)) {


           scene->addItem(newItem->getShape());

       }


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
    exitAction->setStatusTip(tr("Quit"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    saveAction = new QAction(tr("Save"), this);
    saveAction->setShortcuts(QKeySequence::Save);
    saveAction->setStatusTip(tr("Save"));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(saveToFile()));

    loadAction = new QAction(tr("Load"), this);
    loadAction->setStatusTip(tr("Load"));
    connect(loadAction, SIGNAL(triggered()), this, SLOT(loadFromfile()));


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
    fileMenu->addAction(saveAction);
    fileMenu->addAction(loadAction);
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

    QToolButton *polygonePointerButton = new QToolButton;
    polygonePointerButton->setCheckable(true);
    polygonePointerButton->setIcon(QIcon(":/Images/polygone.png"));

    pointerTypeGroup = new QButtonGroup(this);
    pointerTypeGroup->addButton(pointerButton, int(DrawScene::MoveItem));
    pointerTypeGroup->addButton(linePointerButton, int(DrawScene::InsertLine));
    pointerTypeGroup->addButton(ellipsePointerButton, int(DrawScene::InsertEllipse));
    pointerTypeGroup->addButton(polygonePointerButton, int(DrawScene::InsertPolygone));

    connect(pointerTypeGroup, SIGNAL(buttonClicked(int)),
            this, SLOT(pointerGroupClicked(int)));

    pointerToolbar = addToolBar(tr("Pointer type"));
    pointerToolbar->addWidget(pointerButton);
    pointerToolbar->addWidget(linePointerButton);
    pointerToolbar->addWidget(ellipsePointerButton);
    pointerToolbar->addWidget(polygonePointerButton);

}

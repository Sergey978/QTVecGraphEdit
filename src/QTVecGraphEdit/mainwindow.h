#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtSvg/QSvgGenerator>
#include <QMainWindow>
#include"shapeitem.h"

QT_BEGIN_NAMESPACE
class DrawScene;
class QGraphicsView;
class QAction;
class QButtonGroup;
class QGraphicsItem;
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();

private slots:
    void buttonGroupClicked(int id);
    void itemInserted(ShapeItem *item);
    void pointerGroupClicked(int id);

    void itemSelected(QGraphicsItem *item);
    void deleteItem();
    void saveToFile();
    void loadFromfile();

    void about();

private:
    void createActions();
    void createMenus();
    void createToolbars();

    DrawScene *scene;
    QGraphicsView *view;

    QMenu *fileMenu;
    QMenu *itemMenu;
    QMenu *aboutMenu;

    QToolBar *editToolBar;
    QToolBar *pointerToolbar;

    QAction *saveAction;
    QAction *loadAction;
    QAction *exitAction;
    QAction *deleteAction;
    QAction *aboutAction;


    QButtonGroup *buttonGroup;
    QButtonGroup *pointerTypeGroup;

};


#endif // MAINWINDOW_H

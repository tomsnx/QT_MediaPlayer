#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QToolBar>
#include <QLabel>

#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QDragEnterEvent>
#include <QMimeData>

#include <dropArea.h>
#include <menubar.h>
#include <sidebar.h>
#include <playerbar.h>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    int buttonSize = 30;
    QSize iconSize(buttonSize - 10, buttonSize - 10);

    // Menu Bar
    MenuBar *menuBar = new MenuBar(this);
    this->setMenuBar(menuBar);

    // Player Bar
    int statusBarHeight = 40;
    PlayerBar *playerBar = new PlayerBar(statusBarHeight, this);
    statusBar()->setStyleSheet("QStatusBar::item { border: 0; padding: 0; margin: 0; }");
    statusBar()->setSizeGripEnabled(false);
    statusBar()->addWidget(playerBar);

    // Two sides of window
    SideBar *sideBar = new SideBar(this);
    DropArea *dropArea = new DropArea(this);

    // Splitter
    QSplitter *splitter = new QSplitter(Qt::Horizontal, this);
    splitter->addWidget(sideBar);
    splitter->addWidget(dropArea);

    splitter->setCollapsible(0, true);
    splitter->setHandleWidth(5);
    splitter->setStyleSheet("QSplitter::handle {"
                            "background-color: #000000;"
                            "}");

    setCentralWidget(splitter);

    QList<int> sizes;
    sizes << 100 << width() - 100;
    splitter->setSizes(sizes);
}

MainWindow::~MainWindow()
{
    delete ui;
}

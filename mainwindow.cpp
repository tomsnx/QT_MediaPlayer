#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    int buttonSize = 30;
    QSize iconSize(buttonSize - 10, buttonSize - 10);

    player = new QMediaPlayer(this);
    videoArea = new VideoArea(this);
    sideBar = new SideBar(this);
    isPlaying = false;

    // Menu Bar
    menuBar = new MenuBar(player, videoArea, &isPlaying, this);
    this->setMenuBar(menuBar);

    // Player Bar
    int statusBarHeight = 35;
    playerBar = new PlayerBar(statusBarHeight, player, videoArea, sideBar, &isPlaying, this);

    mainWindowVBox = new QVBoxLayout(this);
    mainWindowVBox->setContentsMargins(QMargins(0,0,0,0));
    mainWindowVBox->setSpacing(0);

    // Splitter
    splitter = new QSplitter(Qt::Horizontal, this);
    splitter->addWidget(sideBar);
    splitter->addWidget(videoArea);

    splitter->setCollapsible(0, true);
    splitter->setHandleWidth(5);
    splitter->setStyleSheet("QSplitter::handle {"
                            "background-color: #000000;"
                            "border-bottom: 2px solid black;"
                            "}");

    mainWindowVBox->addWidget(splitter);
    mainWindowVBox->addWidget(playerBar);

    videoArea->setMediaPlayer(player);

    containerWidget = new QWidget;
    containerWidget->setLayout(mainWindowVBox);

    setCentralWidget(containerWidget);

    QList<int> sizes;
    sizes << 100 << width() - 100;
    splitter->setSizes(sizes);

    connect(videoArea, &VideoArea::fileDropped, this, &MainWindow::playVideo);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::playVideo(const QString &filePath) {
    player->setSource(QUrl::fromLocalFile(filePath));
    videoArea->showVideo(true);
    sideBar->setVisible(false);

    player->play();
    isPlaying = true;

    playerBar->updatePlayerButton(&isPlaying);
    playerBar->updateStopButton(&isPlaying);
}

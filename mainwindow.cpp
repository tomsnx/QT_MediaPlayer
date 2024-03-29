#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    int buttonSize = 30;
    QSize iconSize(buttonSize - 10, buttonSize - 10);

    player = new QMediaPlayer(this);
    videoArea = new VideoArea(player, this);
    sideBar = new SideBar(videoArea, this);
    isPlaying = false;

    //sideBar->hide();
    sideBar->setMaximumWidth(300);

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

    splitter->setChildrenCollapsible(true);
    splitter->setHandleWidth(1);
    splitter->setStretchFactor(1, 1);

    mainWindowVBox->addWidget(splitter);
    mainWindowVBox->addWidget(playerBar);

    mainWindowVBox->setContentsMargins(0, 0, 0, 0);

    videoArea->setMediaPlayer(player);

    containerWidget = new QWidget;
    containerWidget->setLayout(mainWindowVBox);

    setCentralWidget(containerWidget);

    QList<int> sizes;
    sizes << 170 << width() - 100;
    splitter->setSizes(sizes);
    splitter->setHandleWidth(1);
    //TODO: Faire en sorte que quand on ferme le splitter a gauche
    // on puisse le réouvrir.

    connect(videoArea, &VideoArea::itemClicked, this, &MainWindow::playVideo);
    connect(videoArea, &VideoArea::fileDroppedInArea, this, &MainWindow::handleFileDropped);

    qApp->setStyleSheet(R"(
        QSplitter::handle {
            background: #c0c0c0;
        }
    )");

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
}

void MainWindow::closeEvent(QCloseEvent *event) {
    videoArea->mediaLibraryWidget->saveToJSON("mediaLibrary.json");
    QMainWindow::closeEvent(event);
}

void MainWindow::handleFileDropped(const QString& filePath) {
    if (sideBar->getCurrentItemText() == "Playlist") {
        videoArea->playlistWidget->addToTable(filePath);
        playVideo(filePath);
    } else if (sideBar->getCurrentItemText() == "Media Library") {
        videoArea->mediaLibraryWidget->addToTable(filePath);
    }
}

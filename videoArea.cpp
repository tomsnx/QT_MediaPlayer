#include "videoArea.h"

VideoArea::VideoArea(QMediaPlayer *player, QWidget *parent) : QWidget(parent) {
    this->player = player;

    videoWidget = new QVideoWidget(this);
    videoWidget->hide();

    playlistWidget = new CustomTable(QString("Playlist"), this);
    mediaLibraryWidget = new CustomTable(QString("Media Library"), this);

    mediaLibraryWidget->loadFromJSON("mediaLibrary.json");

    myVideosWidget = new CustomTable(QString("My Videos"), this);
    musicWidget = new CustomTable(QString("My Music"), this);

    connect(playlistWidget, &CustomTable::copyItemToMediaLibrary, this, &VideoArea::copyItemToMediaLibraryFromPlaylist);
    connect(myVideosWidget, &CustomTable::copyItemToMediaLibrary, this, &VideoArea::copyItemToMediaLibraryFromMyVideos);

    setAcceptDrops(true);

    dropMessageLabel = new QLabel(this);
    dropMessageLabel->setAlignment(Qt::AlignCenter);
    dropMessageLabel->setText("<html><body>"
                              "<p><img src=':/icons/download.png' widht='106' height='106'></p>"
                              "<p>Drop media here</p>"
                              "</body></html>");
    dropMessageLabel->setStyleSheet("border: none; color: grey;");
    dropMessageLabel->show();

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(dropMessageLabel);
    layout->setAlignment(dropMessageLabel, Qt::AlignCenter);
    layout->addWidget(videoWidget);
    layout->addWidget(playlistWidget);
    layout->addWidget(mediaLibraryWidget);
    layout->addWidget(myVideosWidget);
    layout->addWidget(musicWidget);
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);

    connect(playlistWidget, &CustomTable::itemDoubleClicked, this, &VideoArea::playVideo);
    connect(mediaLibraryWidget, &CustomTable::itemDoubleClicked, this, &VideoArea::playVideo);
    connect(myVideosWidget, &CustomTable::itemDoubleClicked, this, &VideoArea::playVideo);
}

void VideoArea::dragEnterEvent(QDragEnterEvent *event) {
    if (event->mimeData()->hasUrls()) {
        event->acceptProposedAction();
    }
}

void VideoArea::dropEvent(QDropEvent *event) {
    const QMimeData *mimeData = event->mimeData();

    if (mimeData->hasUrls()) {
        QList<QUrl> urlList = mimeData->urls();

        if (!urlList.isEmpty() && urlList.first().isLocalFile()) {
            QString filePath = urlList.first().toLocalFile();
            if (!urlList.isEmpty()) {
                filePath = urlList.first().toLocalFile();
                if (!filePath.isEmpty()) {
                    emit fileDroppedInArea(filePath);
                }
            }
        }
    }
}

void VideoArea::setMediaPlayer(QMediaPlayer *player) {
    player->setVideoOutput(videoWidget);
}

void VideoArea::showVideo(bool var) {
    if (var) {
        dropMessageLabel->hide();
        videoWidget->show();
        playlistWidget->hide();
        mediaLibraryWidget->hide();
        myVideosWidget->hide();
        musicWidget->hide();
    }
    else {
        videoWidget->hide();
        playlistWidget->show();
        dropMessageLabel->show();
    }
}

void VideoArea::playVideo(QString filePath) {
    playlistWidget->hide();
    mediaLibraryWidget->hide();
    myVideosWidget->hide();
    musicWidget->hide();

    emit itemClicked(filePath);
}

void VideoArea::copyItemToMediaLibraryFromPlaylist(QTableWidgetItem *item)
{
    QString title = item->text();
    QString filePath = playlistWidget->videoPathMap->value(title);

    if (!filePath.isEmpty()) {
        mediaLibraryWidget->addToTable(filePath);
    }
}

void VideoArea::copyItemToMediaLibraryFromMyVideos(QTableWidgetItem *item)
{
    QString title = item->text();
    QString filePath = myVideosWidget->videoPathMap->value(title);

    if (!filePath.isEmpty()) {
        mediaLibraryWidget->addToTable(filePath);
    }
}

#include "videoArea.h"
#include <QMimeData>
#include <QUrl>
#include <QVBoxLayout>

VideoArea::VideoArea(QWidget *parent) : QWidget(parent) {
    videoWidget = new QVideoWidget(this);
    setAcceptDrops(true);
    videoWidget->hide();

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(videoWidget);
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);
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

        for (const QUrl &url : urlList) {
            qDebug() << "Received URL:" << url.toString();
            if (url.isLocalFile()) {
                qDebug() << "Local file path:" << url.toLocalFile();
            } else {
                qDebug() << "URL is not a local file.";
            }
        }

        QString filePath;
        if (!urlList.isEmpty()) {
            filePath = urlList.first().toLocalFile();
            if (!filePath.isEmpty()) {
                emit fileDropped(filePath);
            }
        }
    }
}

void VideoArea::setMediaPlayer(QMediaPlayer *player) {
    player->setVideoOutput(videoWidget);
}

void VideoArea::showVideo(bool var) {
    var ? videoWidget->show() : videoWidget->hide();
}

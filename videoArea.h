#ifndef DROPAREA_H
#define DROPAREA_H

#include <QObject>
#include <QWidget>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QtMultimediaWidgets>
#include <QtMultimedia>
#include <QtGui>
#include <QTableWidget>
#include <QMimeData>
#include <QUrl>
#include <QVBoxLayout>
#include <QString>

#include <customtable.h>

class VideoArea : public QWidget {
    Q_OBJECT

signals:
    void fileDropped(const QString &filePath);
    void itemClicked(const QString &filePath);

public:
    explicit VideoArea(QMediaPlayer *player, QWidget *parent = nullptr);
    void setMediaPlayer(QMediaPlayer *player);
    void showVideo(bool);

    QLabel *dropMessageLabel;
    QVideoWidget *videoWidget;
    CustomTable *playlistWidget, *mediaLibraryWidget, *myVideosWidget, *musicWidget;

private slots:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    void playVideo(QString filePath);

private:
    void showPlaylistContextMenu(const QPoint &pos);
    void copyItemToMediaLibrary(QTableWidgetItem *item);
    QMap<QString, QString> videoPathMap;

protected:
    QMediaPlayer *player;
};

#endif // DROPAREA_H

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

class VideoArea : public QWidget {
    Q_OBJECT
signals:
    void fileDropped(const QString &filePath);

public:
    explicit VideoArea(QWidget *parent = nullptr);
    void setMediaPlayer(QMediaPlayer *player);
    void showVideo(bool);
    void addToPlaylist(const QString &filePath);

    QLabel *dropMessageLabel;
    QVideoWidget *videoWidget;
    QTableWidget *playlistWidget, *mediaLibraryWidget;

private slots:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);

private:
    void showPlaylistContextMenu(const QPoint &pos);
    void copyItemToMediaLibrary(QTableWidgetItem *item);

protected:
    QMediaPlayer *player;
};

#endif // DROPAREA_H

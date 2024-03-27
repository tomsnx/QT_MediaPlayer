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
    void itemClicked(const QString &filePath);

public:
    explicit VideoArea(QMediaPlayer *player, QWidget *parent = nullptr);
    void setMediaPlayer(QMediaPlayer *player);
    void showVideo(bool);
    void addToPlaylist(const QString &filePath);

    QLabel *dropMessageLabel;
    QVideoWidget *videoWidget;
    QTableWidget *playlistWidget, *mediaLibraryWidget;

private slots:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    void playVideoFromPlaylist(QTableWidgetItem *item);

private:
    void showPlaylistContextMenu(const QPoint &pos);
    void copyItemToMediaLibrary(QTableWidgetItem *item);

    QMap<QString, QString> videoPathMap;

protected:
    QMediaPlayer *player;
};

#endif // DROPAREA_H

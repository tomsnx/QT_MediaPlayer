#ifndef MENUBAR_H
#define MENUBAR_H

#include <QObject>
#include <QMenuBar>
#include <QFileDialog>
#include <QMediaPlayer>
#include <videoArea.h>

class MenuBar : public QMenuBar
{
    Q_OBJECT
public:
    explicit MenuBar(QMediaPlayer *player, VideoArea *videoArea, bool *isPlaying, QWidget *parent = nullptr);

private:
    QMenuBar *menuBar;
    QMenu *fileMenu, *audioMenu, *videoMenu, *subtitleMenu;
    QAction *openFolder,
            *newAction,
            *openAction,
            *IncreaseAction,
            *DecreaseAction,
            *MuteAction,
            *sizeAction,
            *colorAction,
            *bkgColorAction;

    QMediaPlayer *player;
    VideoArea *videoArea;
    bool *isPlaying;

};
#endif // MENUBAR_H

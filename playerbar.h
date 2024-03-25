#ifndef PLAYERBAR_H
#define PLAYERBAR_H

#include <QWidget>
#include <QPushButton>
#include <QSlider>
#include <QLabel>
#include <QHBoxLayout>
#include <QStyle>
#include <QMediaPlayer>
#include <videoArea.h>
#include <sidebar.h>


class PlayerBar : public QWidget {
    Q_OBJECT

public:
    explicit PlayerBar(int height, QMediaPlayer *player, VideoArea *videoArea, SideBar *sideBar, bool *isPlaying, QWidget *parent = nullptr);

    void updatePlayerButton(bool *isPLaying);
    void updateStopButton(bool *isPLaying);

private slots:
    void onProgressSliderMoved(int position);

private:
    int height;
    QHBoxLayout *globalLayout, *progressLayout, *playerLayout, *playButtonLayout, *soundLayout;
    QWidget *playerWidget, *soundWidget;
    QPushButton *playPauseButton;
    QPushButton *stopButton;
    QPushButton *nextButton;
    QPushButton *previousButton;
    QPushButton *fullScreenButton;
    QSlider *progressSlider;
    QSlider *soundSlider;
    QLabel *currentTimeLabel;
    QLabel *totalTimeLabel;
    QLabel *volumeMuted;
    QString *sliderStyle;
    QMediaPlayer *player;
    VideoArea *videoArea;
    SideBar *sideBar;
    QAudioOutput *audioOutput;

    QString formatTime(qint64 timeMilliSeconds);

    bool *isPlaying;
    bool userIsInteractingWithSlider;
    bool isStoped;

    void initStyles();
    void initPlayerButtons(QSize &size);
    void initProgressBar();
    void initSoundSettings();
    void initLayouts();

    void initPlayPauseButton();
};

#endif // PLAYERBAR_H

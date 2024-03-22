#ifndef PLAYERBAR_H
#define PLAYERBAR_H

#include <QWidget>
#include <QPushButton>
#include <QSlider>
#include <QLabel>
#include <QHBoxLayout>

class PlayerBar : public QWidget {
    Q_OBJECT

public:
    explicit PlayerBar(int height, QWidget *parent = nullptr);

private slots:
    void onPlayButtonClicked();
    void onPauseButtonClicked();
    void onStopButtonClicked();
    void onNextButtonClicked();
    void onPreviousButtonClicked();
    void onFullScreenClicked();
    void onProgressSliderMoved(int position);

private:
    int height;
    QHBoxLayout *globalLayout, *progressLayout, *playerLayout, *soundLayout;
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
};

#endif // PLAYERBAR_H

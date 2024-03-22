#include "PlayerBar.h"
#include <QStyle>

PlayerBar::PlayerBar(int height, QWidget *parent) : QWidget(parent) {
    this->setFixedHeight(height);

    QString sliderStyle = R"(
        QSlider::groove:horizontal {
            border: 1px solid #999999;
            height: 8px; /* the height of the groove */
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #b1b1b1, stop:1 #c4c4c4);
            margin: 2px 0;
            border-radius: 3px;
        }

        QSlider::handle:horizontal {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #b4b4b4, stop:1 #dcdcdc);
            border: 1px solid #5c5c5c;
            width: 18px;
            margin: -4px 0; /* handle is placed by default on the contents rect of the groove. Expand outside the groove */
            border-radius: 3px;
        }

        QSlider::sub-page:horizontal {
            background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #5DCCFF, stop: 1 #1874CD);
            border: 1px solid #777;
            height: 10px;
            border-radius: 3px;
        }
    )";

    previousButton = new QPushButton("", this);
    previousButton->setIcon(style()->standardIcon(QStyle::SP_MediaSeekBackward));
    previousButton->setEnabled(false);
    previousButton->setFixedHeight(30);

    playPauseButton = new QPushButton("", this);
    playPauseButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    playPauseButton->setFixedHeight(30);

    nextButton = new QPushButton("", this);
    nextButton->setIcon(style()->standardIcon(QStyle::SP_MediaSeekForward));
    nextButton->setEnabled(false);
    nextButton->setFixedHeight(30);

    stopButton = new QPushButton("", this);
    stopButton->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
    stopButton->setEnabled(false);
    stopButton->setFixedHeight(30);

    fullScreenButton = new QPushButton("", this);
    fullScreenButton->setIcon(style()->standardIcon(QStyle::SP_TitleBarMaxButton));
    fullScreenButton->setFixedHeight(30);

    soundSlider = new QSlider(Qt::Horizontal, this);
    soundSlider->setRange(0, 100);
    soundSlider->setFixedWidth(75);
    soundSlider->setValue(50);
    soundSlider->setFixedHeight(30);

    volumeMuted = new QLabel(this);
    volumeMuted->setPixmap(style()->standardIcon(QStyle::SP_MediaVolume).pixmap(24, 24));
    volumeMuted->setFixedHeight(30);

    currentTimeLabel = new QLabel("00:00", this);
    currentTimeLabel->setFixedHeight(30);

    progressSlider = new QSlider(Qt::Horizontal, this);
    progressSlider->setRange(0, 100);
    progressSlider->setEnabled(true);
    progressSlider->setStyleSheet(sliderStyle);
    progressSlider->setFixedHeight(30);

    totalTimeLabel = new QLabel("00:00", this);
    totalTimeLabel->setFixedHeight(30);

    playerLayout = new QHBoxLayout();
    playerLayout->addWidget(previousButton);
    playerLayout->addWidget(playPauseButton);
    playerLayout->addWidget(nextButton);
    playerLayout->addWidget(stopButton);

    progressLayout = new QHBoxLayout();
    progressLayout->addWidget(currentTimeLabel);
    progressLayout->addWidget(progressSlider);
    progressLayout->addWidget(totalTimeLabel);

    soundLayout = new QHBoxLayout();
    soundLayout->addWidget(volumeMuted);
    soundLayout->addWidget(soundSlider);

    globalLayout = new QHBoxLayout();

    globalLayout->addLayout(playerLayout);
    globalLayout->addLayout(progressLayout);
    globalLayout->addLayout(soundLayout);
    globalLayout->addWidget(fullScreenButton);

    setLayout(globalLayout);

    // Connect signals to slots
    connect(playPauseButton, &QPushButton::clicked, this, &PlayerBar::onPlayButtonClicked);
    // ... other connections
}


// Implementation of slots
void PlayerBar::onPlayButtonClicked() {
    // Slot implementation
}

void PlayerBar::onPauseButtonClicked() {
    // Slot implementation
}

void PlayerBar::onStopButtonClicked() {
    // Slot implementation
}

void PlayerBar::onNextButtonClicked() {
    // Slot implementation
}

void PlayerBar::onPreviousButtonClicked() {
    // Slot implementation
}

void PlayerBar::onFullScreenClicked() {
    // Slot implementation
}

void PlayerBar::onProgressSliderMoved(int position) {
    // Slot implementation
}

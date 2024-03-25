#include "playerBar.h"
#include <button.h>

PlayerBar::PlayerBar(int height, QMediaPlayer *player, VideoArea *VideoArea, SideBar *sideBar, bool *isPlaying, QWidget *parent) : QWidget(parent) {
    this->player = player;
    this->videoArea = VideoArea;
    this->sideBar = sideBar;
    this->isPlaying = isPlaying;

    userIsInteractingWithSlider = false;
    isStoped = false;

    this->setFixedHeight(height);
    this->setContentsMargins(QMargins(0,0,0,0));

    QSize *buttonSize = new QSize(30, 30);

    audioOutput = new QAudioOutput(this);
    player->setAudioOutput(audioOutput);
    audioOutput->setVolume(0.5);

    this->initStyles();
    this->initPlayerButtons(*buttonSize);
    this->initProgressBar();
    this->initSoundSettings();

    fullScreenButton = new Button(*buttonSize,
                            style()->standardIcon(QStyle::SP_TitleBarMaxButton),
                            this);

    QObject::connect(fullScreenButton, &QPushButton::clicked, this, [this]() {
        QWidget *mainWindow = this->window();
        if (mainWindow->isMaximized()) {
            mainWindow->showNormal();
        } else {
            mainWindow->showMaximized();
        }
    });

    //Media Player Settings
    QObject::connect(player, &QMediaPlayer::positionChanged, this, [this, player](qint64 position) {
        if (!userIsInteractingWithSlider) {
            progressSlider->setSliderPosition(static_cast<int>((static_cast<double>(position) / player->duration()) * 100));
            currentTimeLabel->setText(formatTime(position));
        }
    });

    // Connecter le signal durationChanged à une lambda pour mettre à jour le temps total
    QObject::connect(player, &QMediaPlayer::durationChanged, this, [this](qint64 duration) {
        totalTimeLabel->setText(formatTime(duration));
    });

    this->initLayouts();

    setLayout(globalLayout);
}

void PlayerBar::initStyles() {
    sliderStyle = new QString(R"(
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
    )");
}

void PlayerBar::initPlayerButtons(QSize &buttonsSize)
{
    previousButton = new Button(buttonsSize,
                                style()->standardIcon(QStyle::SP_MediaSeekBackward),
                                this);
    previousButton->setEnabled(false);

    playPauseButton = new Button(buttonsSize,
                                 style()->standardIcon(QStyle::SP_MediaPlay),
                                 this);

    initPlayPauseButton();



    nextButton = new Button(buttonsSize,
                            style()->standardIcon(QStyle::SP_MediaSeekForward),
                            this);
    nextButton->setEnabled(false);

    playButtonLayout = new QHBoxLayout();
    playButtonLayout->addWidget(previousButton);
    playButtonLayout->addWidget(playPauseButton);
    playButtonLayout->addWidget(nextButton);
    playButtonLayout->setSpacing(0);
    playButtonLayout->setContentsMargins(0, 0, 0, 0);

    stopButton = new Button(buttonsSize,
                            style()->standardIcon(QStyle::SP_MediaStop),
                            this);
    stopButton->setEnabled(false);

    QObject::connect(stopButton, &QPushButton::clicked, this, [this]() {
        *isPlaying = false;
        isStoped = !isStoped;
        player->stop();
        videoArea->videoWidget->hide();
        sideBar->setVisible(true);
        updatePlayerButton(isPlaying);
        progressSlider->setEnabled(false);

        initPlayPauseButton();
    });
}

void PlayerBar::initProgressBar()
{
    currentTimeLabel = new QLabel("00:00", this);
    currentTimeLabel->setFixedHeight(30);

    progressSlider = new QSlider(Qt::Horizontal, this);
    progressSlider->setRange(0, 100);
    progressSlider->setEnabled(false);
    progressSlider->setStyleSheet(*sliderStyle);
    progressSlider->setFixedHeight(30);

    QObject::connect(progressSlider, &QSlider::sliderPressed, this, [this]() {
        userIsInteractingWithSlider = true;
    });

    // Signal pour définir la position lorsque l'utilisateur déplace le slider
    QObject::connect(progressSlider, &QSlider::sliderMoved, this, [this](int position) {
        qint64 videoPosition = static_cast<qint64>((position / 100.0) * player->duration());
        currentTimeLabel->setText(formatTime(videoPosition));
    });

    // Signal pour relancer la mise à jour automatique et ajuster la position de la vidéo lorsque l'utilisateur relâche le slider
    QObject::connect(progressSlider, &QSlider::sliderReleased, this, [this]() {
        qint64 videoPosition = static_cast<qint64>((progressSlider->value() / 100.0) * player->duration());
        player->setPosition(videoPosition);
        userIsInteractingWithSlider = false;
        if (*isPlaying) {
            player->play();
        }
    });

    totalTimeLabel = new QLabel("00:00", this);
    totalTimeLabel->setFixedHeight(30);
}

void PlayerBar::initSoundSettings()
{
    volumeMuted = new QLabel(this);
    volumeMuted->setPixmap(style()->standardIcon(QStyle::SP_MediaVolume).pixmap(24, 24));
    volumeMuted->setFixedHeight(30);

    soundSlider = new QSlider(Qt::Horizontal, this);
    soundSlider->setRange(0, 100);
    soundSlider->setFixedWidth(75);
    soundSlider->setValue(50);
    soundSlider->setFixedHeight(30);

    QObject::connect(soundSlider, &QSlider::valueChanged, this, [this](int value) {
        qreal volumeLevel = value / 100.0;
        audioOutput->setVolume(volumeLevel);
    });
}

void PlayerBar::initLayouts()
{
    playerLayout = new QHBoxLayout();
    playerLayout->addLayout(playButtonLayout);
    playerLayout->addWidget(stopButton);

    progressLayout = new QHBoxLayout();
    progressLayout->addWidget(currentTimeLabel);
    progressLayout->addWidget(progressSlider);
    progressLayout->addWidget(totalTimeLabel);

    playerLayout->setContentsMargins(0, 0, 0, 0);
    progressLayout->setContentsMargins(0, 0, 0, 0);

    globalLayout = new QHBoxLayout();
    globalLayout->setContentsMargins(0, 0, 0, 0);
    globalLayout->addLayout(playerLayout);
    globalLayout->addLayout(progressLayout);
    globalLayout->addWidget(volumeMuted);
    globalLayout->addWidget(soundSlider);
    globalLayout->addWidget(fullScreenButton);
}

void PlayerBar::updatePlayerButton(bool *isPlaying)
{
    if (*isPlaying)
    {
        progressSlider->setEnabled(true);
        playPauseButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
        stopButton->setDisabled(false);
        QObject::disconnect(playPauseButton, &QPushButton::clicked, this, nullptr);
        QObject::connect(playPauseButton, &QPushButton::clicked, this, [this, isPlaying]() {
            *isPlaying = false;
            player->pause();
            updatePlayerButton(isPlaying);
        });
    }
    else
    {
        playPauseButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        QObject::disconnect(playPauseButton, &QPushButton::clicked, this, nullptr);
        QObject::connect(playPauseButton, &QPushButton::clicked, this, [this, isPlaying]() {
            *isPlaying = true;
            player->play();
            updatePlayerButton(isPlaying);
        });
    }
}

void PlayerBar::updateStopButton(bool *isPlaying)
{

}

void PlayerBar::initPlayPauseButton()
{
    QObject::disconnect(playPauseButton, &QPushButton::clicked, this, nullptr);
    QObject::connect(playPauseButton, &QPushButton::clicked, this, [this]() {
        QString fileName = QFileDialog:: getOpenFileName(this,tr("Select Video File"),"",tr("MP4 Files (*.MP4)")) ;
        if (!fileName.isEmpty()) {
            player->setSource(QUrl::fromLocalFile(fileName));
            videoArea->showVideo(true);
            player->play();
            *isPlaying = true;
            updatePlayerButton(isPlaying);
        }
    });
}

QString PlayerBar::formatTime(qint64 timeMilliSeconds) {
    int seconds = static_cast<int>(timeMilliSeconds / 1000) % 60;
    int minutes = static_cast<int>(timeMilliSeconds / (1000 * 60)) % 60;
    int hours = static_cast<int>(timeMilliSeconds / (1000 * 60 * 60)) % 24;

    QTime time(hours, minutes, seconds);
    return time.toString(hours > 0 ? "hh:mm:ss" : "mm:ss");
}

// Implementation of slots
void PlayerBar::onProgressSliderMoved(int position) {
    // Slot implementation
}

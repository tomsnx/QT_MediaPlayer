#include "menubar.h"

MenuBar::MenuBar(QMediaPlayer *player, VideoArea *videoArea, bool *isPlaying, QWidget *parent) : QMenuBar(parent)
{
    this->player = player;
    this->videoArea = videoArea;
    this->isPlaying = isPlaying;

    QMenu *fileMenu = this->addMenu(tr("&Fichier"));
    QMenu *audioMenu = this->addMenu(tr("&Audio"));
    QMenu *videoMenu = this->addMenu(tr("&Vidéo"));
    QMenu *subtitleMenu = this->addMenu(tr("&Sous-Titres"));

    QAction *openFolder = fileMenu->addAction(tr("Ouvrir un dossier"));
    QAction *newAction = fileMenu->addAction(tr("Nouveau"));
    QAction *openAction = fileMenu->addAction(tr("Ouvrir"));

    /*QObject::connect(openAction, &QAction::triggered, this, [this]() {
        QString fileName = QFileDialog::getOpenFileName(this, tr("Select Video File"), "", tr("Video Files (*.mp4 *.avi *.mkv)"));
        if (!fileName.isEmpty()) {
            player->setSource(QUrl::fromLocalFile(fileName));
            videoArea->showVideo(true);
            player->play();
            *isPlaying = true;
            updatePlayerButton(isPlaying);
        }
    });*/

    QAction *IncreaseAction = audioMenu->addAction(tr("Augmenter"));
    QAction *DecreaseAction = audioMenu->addAction(tr("Diminuer"));
    QAction *MuteAction = audioMenu->addAction(tr("Mute"));

    QAction *sizeAction = subtitleMenu->addAction(tr("Size"));
    QAction *colorAction = subtitleMenu->addAction(tr("Color"));
    QAction *bkgColorAction = subtitleMenu->addAction(tr("Couleur d'arrière-plan"));
}

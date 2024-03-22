#include "menubar.h"

MenuBar::MenuBar(QWidget *parent) : QMenuBar(parent)
{

    QMenu *fileMenu = this->addMenu(tr("&Fichier"));
    QMenu *audioMenu = this->addMenu(tr("&Audio"));
    QMenu *videoMenu = this->addMenu(tr("&Vidéo"));
    QMenu *subtitleMenu = this->addMenu(tr("&Sous-Titres"));

    QAction *openFolder = fileMenu->addAction(tr("Ouvrir un dossier"));
    QAction *newAction = fileMenu->addAction(tr("Nouveau"));
    QAction *openAction = fileMenu->addAction(tr("Ouvrir"));

    QAction *IncreaseAction = audioMenu->addAction(tr("Augmenter"));
    QAction *DecreaseAction = audioMenu->addAction(tr("Diminuer"));
    QAction *MuteAction = audioMenu->addAction(tr("Mute"));

    QAction *sizeAction = subtitleMenu->addAction(tr("Size"));
    QAction *colorAction = subtitleMenu->addAction(tr("Color"));
    QAction *bkgColorAction = subtitleMenu->addAction(tr("Couleur d'arrière-plan"));
}

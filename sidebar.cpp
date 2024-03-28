#include "sideBar.h"

SideBar::SideBar(VideoArea *videoArea, QWidget *parent) : QWidget(parent) {
    layout = new QVBoxLayout(this);
    this->videoArea = videoArea;
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    // Création du QListWidget
    listWidget = new QListWidget(this);
    listWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    listWidget->setContentsMargins(QMargins(0, 0, 0, 0));
    listWidget->setSelectionMode(QAbstractItemView::SingleSelection);


    QFont headerFont;
    headerFont.setBold(true);
    headerFont.setPointSize(12);
    QBrush headerBrush(Qt::black);

    headerItem = new QListWidgetItem("LIBRARY");
    headerItem->setFont(headerFont);
    headerItem->setForeground(headerBrush);
    headerItem->setFlags(headerItem->flags() & ~Qt::ItemIsSelectable & ~Qt::ItemIsEnabled);
    listWidget->addItem(headerItem);

    QFont itemFont;
    itemFont.setBold(false);
    itemFont.setPointSize(13);

    QIcon playlistIcon(":/icons/music.png");
    QIcon filmIcon(":/icons/film.png");
    QIcon musicalNoteIcon(":/icons/musical-note.png");

    item = new QListWidgetItem(playlistIcon, "Playlist");
    item->setFont(itemFont);
    listWidget->addItem(item);

    item = new QListWidgetItem(playlistIcon, "Media Library");
    item->setFont(itemFont);
    listWidget->addItem(item);

    // Espace entre les sections
    spaceLabel = new QLabel(this);
    spaceLabel->setFixedHeight(10);
    layout->addWidget(spaceLabel);

    // Deuxième section
    headerItem = new QListWidgetItem("MY COMPUTER");
    headerItem->setFont(headerFont);
    headerItem->setForeground(headerBrush);
    headerItem->setFlags(headerItem->flags() & ~Qt::ItemIsSelectable & ~Qt::ItemIsEnabled);
    listWidget->addItem(headerItem);

    item = new QListWidgetItem(filmIcon, "My Videos");
    item->setFont(itemFont);
    listWidget->addItem(item);

    item = new QListWidgetItem(musicalNoteIcon, "My Music");
    item->setFont(itemFont);
    listWidget->addItem(item);

    // Style pour la liste
    listWidget->setStyleSheet(R"(
        QListWidget {
            border: none;
            padding: 0px;
            background-color: #d1d1cf;
        }
        QListWidget::item {
            padding: 4px;
            border-radius: 5px;
            margin: 2px;
            background-color: #d1d1cf;
        }
        QListWidget::item:selected {
            background-color: #0078d7;
            color: white;
            border: 1px solid #d1d1cf;
            border-radius: 8px;
        }
        QListWidget::item:disabled {
            font-weight: bold;
            background-color: #d1d1cf;
            color: black;
        }
    )");

    connect(listWidget, &QListWidget::currentItemChanged, this, &SideBar::handleSelectionChanged);

    layout->addWidget(listWidget);
    setLayout(layout);
}

void SideBar::handleSelectionChanged(QListWidgetItem *current, QListWidgetItem *previous) {
    Q_UNUSED(previous)

    // Cachez tous les widgets pour commencer
    videoArea->playlistWidget->hide();
    videoArea->mediaLibraryWidget->hide();
    videoArea->dropMessageLabel->hide();
    videoArea->myVideosWidget->hide();
    videoArea->musicWidget->hide();

    // Affichez le widget approprié en fonction de l'élément sélectionné
    if (current->text() == "Playlist") {
        if (videoArea->playlistWidget->tableWidget->rowCount() == 0) {
            videoArea->dropMessageLabel->show();
        } else {
            videoArea->playlistWidget->show();
        }
    } else if (current->text() == "Media Library") {
        videoArea->mediaLibraryWidget->show();
    }
    else if (current->text() == "My Videos") {
        videoArea->myVideosWidget->show();
    }
    else {
        videoArea->musicWidget->show();
    }
    // Ajoutez des conditions supplémentaires pour les autres éléments si nécessaire
}

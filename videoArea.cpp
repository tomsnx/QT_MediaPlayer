#include "videoArea.h"
#include <QMimeData>
#include <QUrl>
#include <QVBoxLayout>

VideoArea::VideoArea(QWidget *parent) : QWidget(parent) {
    videoWidget = new QVideoWidget(this);
    playlistWidget = new QTableWidget(this);
    playlistWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    playlistWidget->setSelectionMode(QAbstractItemView::SingleSelection);

    playlistWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(playlistWidget, &QWidget::customContextMenuRequested, this, &VideoArea::showPlaylistContextMenu);

    connect(playlistWidget, &QTableWidget::itemSelectionChanged, [this]() {
        auto selectedItems = playlistWidget->selectedItems();
        if (!selectedItems.isEmpty()) {
            // Obtenez l'élément de la première colonne de la ligne sélectionnée, qui contient le chemin du fichier
            QTableWidgetItem *item = selectedItems.first();
            int row = item->row();
            QString filePath = playlistWidget->item(row, 0)->text(); // Mettez 0 si le chemin est dans la première colonne

            /*player->setSource(QUrl::fromLocalFile(filePath));
            showVideo(true);
            player->play();*/
        }
    });

    // Configurez tableWidget ici
    playlistWidget->setColumnCount(3);
    playlistWidget->setHorizontalHeaderLabels(QStringList() << "Title" << "Author" << "Duration");
    playlistWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    playlistWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    playlistWidget->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);

    playlistWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    playlistWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    playlistWidget->setAlternatingRowColors(true);
    playlistWidget->setStyleSheet("QTableWidget {"
                                  "    alternate-background-color: #f0f0f0;"
                                  "}"
                                  "QTableWidget::item {"
                                  "    padding: 2px;"
                                  "}"
                                  );

    mediaLibraryWidget = new QTableWidget(this);
    mediaLibraryWidget->hide();
    mediaLibraryWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    mediaLibraryWidget->setSelectionMode(QAbstractItemView::SingleSelection);


    // Configurez tableWidget ici
    mediaLibraryWidget->setColumnCount(3);
    mediaLibraryWidget->setHorizontalHeaderLabels(QStringList() << "Title" << "Author" << "Duration");
    mediaLibraryWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    mediaLibraryWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    mediaLibraryWidget->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);

    mediaLibraryWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    mediaLibraryWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    mediaLibraryWidget->setAlternatingRowColors(true);
    mediaLibraryWidget->setStyleSheet("QTableWidget {"
                                  "    alternate-background-color: #f0f0f0;"
                                  "}"
                                  "QTableWidget::item {"
                                  "    padding: 2px;"
                                  "}"
                                  );

    setAcceptDrops(true);
    videoWidget->hide();
    playlistWidget->hide();

    dropMessageLabel = new QLabel(this);
    dropMessageLabel->setAlignment(Qt::AlignCenter);
    dropMessageLabel->setText("<html><body>"
                              "<p><img src=':/icons/download.png' widht='106' height='106'></p>"  // Remplacez avec le chemin de votre icône
                              "<p>Drop media here</p>"
                              "</body></html>");
    dropMessageLabel->setStyleSheet("border: none; color: grey;");
    dropMessageLabel->show();

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(dropMessageLabel);
    layout->setAlignment(dropMessageLabel, Qt::AlignCenter);
    layout->addWidget(videoWidget);
    layout->addWidget(playlistWidget);
    layout->addWidget(mediaLibraryWidget);    // Ajoutez le tableWidget au layout
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);
}

void VideoArea::dragEnterEvent(QDragEnterEvent *event) {
    if (event->mimeData()->hasUrls()) {
        event->acceptProposedAction();
    }
}

void VideoArea::dropEvent(QDropEvent *event) {
    const QMimeData *mimeData = event->mimeData();

    if (mimeData->hasUrls()) {
        QList<QUrl> urlList = mimeData->urls();

        // Supposons que vous ne prenez que le premier fichier pour l'exemple
        if (!urlList.isEmpty() && urlList.first().isLocalFile()) {
            QString filePath = urlList.first().toLocalFile();
            if (!urlList.isEmpty()) {
                filePath = urlList.first().toLocalFile();
                if (!filePath.isEmpty()) {
                    emit fileDropped(filePath);
                    addToPlaylist(filePath);
                }
            }
        }
    }
}

void VideoArea::addToPlaylist(const QString &filePath) {
    QFileInfo fileInfo(filePath);
    QString title = fileInfo.completeBaseName();
    QString duration = "--:--";

    int currentRow = playlistWidget->rowCount();
    playlistWidget->insertRow(currentRow);

    playlistWidget->setItem(currentRow, 0, new QTableWidgetItem(title));
    playlistWidget->setItem(currentRow, 1, new QTableWidgetItem("Author")); // Mettez à jour avec la vraie valeur
    playlistWidget->setItem(currentRow, 2, new QTableWidgetItem(duration));
}

void VideoArea::setMediaPlayer(QMediaPlayer *player) {
    player->setVideoOutput(videoWidget);
}

void VideoArea::showVideo(bool var) {
    if (var) {
        dropMessageLabel->hide();
        videoWidget->show();
        playlistWidget->hide();
    }
    else {
        videoWidget->hide();
        playlistWidget->show();
        dropMessageLabel->show();
    }
}

void VideoArea::showPlaylistContextMenu(const QPoint &pos) {
    // Trouver l'élément sur lequel le clic droit a été effectué
    QTableWidgetItem *item = playlistWidget->itemAt(pos);
    if (!item) return;

    // Créer le menu contextuel
    QMenu contextMenu(tr("Context menu"), this);

    // Ajouter l'action de copie
    QAction copyAction("Copy to Media Library", this);
    connect(&copyAction, &QAction::triggered, [this, item]() {
        // Copier l'élément dans mediaLibraryWidget
        copyItemToMediaLibrary(item);
    });
    contextMenu.addAction(&copyAction);

    QAction *removeAction = contextMenu.addAction("Delete");
    connect(removeAction, &QAction::triggered, [this, item]() {
        // Supprimer l'élément de playlistWidget
        playlistWidget->removeRow(item->row());
    });

    // Afficher le menu contextuel
    contextMenu.exec(playlistWidget->viewport()->mapToGlobal(pos));
}

void VideoArea::copyItemToMediaLibrary(QTableWidgetItem *item) {
    int row = item->row();

    // Supposons que la colonne 0 contient le titre, 1 l'auteur, 2 la durée
    QString title = playlistWidget->item(row, 0)->text();
    QString author = playlistWidget->item(row, 1)->text();
    QString duration = playlistWidget->item(row, 2)->text();

    // Ajouter ces informations à mediaLibraryWidget
    int newRow = mediaLibraryWidget->rowCount();
    mediaLibraryWidget->insertRow(newRow);
    mediaLibraryWidget->setItem(newRow, 0, new QTableWidgetItem(title));
    mediaLibraryWidget->setItem(newRow, 1, new QTableWidgetItem(author));
    mediaLibraryWidget->setItem(newRow, 2, new QTableWidgetItem(duration));
}

#include "customtable.h"

CustomTable::CustomTable(const QString &title, QWidget *parent) : QWidget(parent), title(title) {

    videoPathMap = new QMap<QString, QString>();
    layout = new QVBoxLayout(this);
    topBar = new QLabel(this);
    topBar->setText(title);
    topBar->setStyleSheet("background-color: #dcdcdc;"
                          "padding-left: 2px");
    topBar->setFixedHeight(25);

    tableWidget = new QTableWidget();
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);

    tableWidget->setColumnCount(3);
    tableWidget->setHorizontalHeaderLabels(QStringList() << "Title" << "Author" << "Duration");
    tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    tableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    tableWidget->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);

    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidget->setAlternatingRowColors(true);
    tableWidget->setStyleSheet("QTableWidget {"
                               "    alternate-background-color: #f0f0f0;"
                               "}"
                               "QTableWidget::item {"
                               "    padding: 2px;"
                               "}"
                              );

    layout->addWidget(topBar);
    layout->addWidget(tableWidget);

    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    this->setLayout(layout);

    connect(tableWidget, &QTableWidget::itemDoubleClicked, this, &CustomTable::onItemDoubleClicked);
    connect(tableWidget, &QTableWidget::customContextMenuRequested, this, &CustomTable::onCustomContextMenuRequested);

    this->hide();
}

void CustomTable::onItemDoubleClicked(QTableWidgetItem *item) {
    int row = item->row();
    QString title = this->tableWidget->item(row, 0)->text();

    QString filePath = this->videoPathMap->value(title);
    if (!filePath.isEmpty()) {
        emit itemDoubleClicked(filePath);
    }
}

void CustomTable::onCustomContextMenuRequested(const QPoint &pos) {
    QTableWidgetItem* item = tableWidget->itemAt(pos);
    QMenu contextMenu;

    contextMenu.setStyleSheet(R"(
                                QMenu {
                                    background-color: #ffffff;
                                    border: 1px solid #cccccc;
                                    border-radius: 4px;
                                }

                                QMenu::item {
                                    padding: 2px 8px;
                                    margin: 1px 4px;
                                    border-radius: 4px;
                                }

                                QMenu::item:selected {
                                    background-color: #0078d7;
                                    color: white;
                                }
                            )");

    if (!item) {
        QAction* addAction = contextMenu.addAction(tr("Ajouter un nouvel élément"));

        connect(addAction, &QAction::triggered, this, [this]() {
            QString filePath = QFileDialog:: getOpenFileName(this,tr("Select Video File"),"",tr("MP4 Files (*.MP4 *.mkv *.avi)"));
            if(!filePath.isEmpty())
            {
                addToTable(filePath);
            }
        });
    } else {

        if (this->title == "Playlist") {
            QAction* copyAction = contextMenu.addAction(tr("Copier dans Media Library"));
            connect(copyAction, &QAction::triggered, this, [this, item]() {
                emit copyItemToMediaLibrary(item);
            });
        }

        QAction* deleteAction = contextMenu.addAction(tr("Supprimer"));
        connect(deleteAction, &QAction::triggered, this, [this, item]() {
            int row = tableWidget->row(item);
            tableWidget->removeRow(row);
        });
    }
    contextMenu.exec(tableWidget->viewport()->mapToGlobal(pos));
}

void CustomTable::addToTable(const QString &filePath)
{
    QFileInfo fileInfo(filePath);
    QString title = fileInfo.completeBaseName();

    int currentRow = this->tableWidget->rowCount();
    this->tableWidget->insertRow(currentRow);

    this->tableWidget->setItem(currentRow, 0, new QTableWidgetItem(title));
    this->tableWidget->setItem(currentRow, 1, new QTableWidgetItem("Author"));
    this->tableWidget->setItem(currentRow, 2, new QTableWidgetItem("--:--"));

    this->videoPathMap->insert(title, filePath);

    // Créez un nouveau lecteur multimédia pour récupérer la durée et d'autres métadonnées
    QMediaPlayer *tempPlayer = new QMediaPlayer;
    tempPlayer->setSource(QUrl::fromLocalFile(filePath));

    //FIXME: A terme faire ça pour récupérer les métadonnées: utilisation d'une bibliothèque tierce comme FFmpeg (via libavformat et libavcodec)
    connect(tempPlayer, &QMediaPlayer::mediaStatusChanged, this, [this, tempPlayer, currentRow](QMediaPlayer::MediaStatus status) mutable {
        if (status == QMediaPlayer::LoadedMedia) {
            qint64 duration = tempPlayer->duration();
            QString durationStr = QTime(0, 0, 0).addMSecs(duration).toString("hh:mm:ss");
            QString author = tempPlayer->metaData().metaDataKeyToString(QMediaMetaData::Author);

            if (author.isEmpty()) {
                author = tempPlayer->metaData().metaDataKeyToString(QMediaMetaData::ContributingArtist);
            }

            this->tableWidget->item(currentRow, 2)->setText(durationStr);
            this->tableWidget->item(currentRow, 1)->setText(!author.isEmpty() ? author : "Unknown");

            tempPlayer->deleteLater();
        }
    });
    tempPlayer->play();
}

CustomTable::~CustomTable() {
    delete videoPathMap;
}

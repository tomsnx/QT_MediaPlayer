#include "customtable.h"

CustomTable::CustomTable(const QString &title, QWidget *parent) : QWidget(parent), title(title) {

    videoPathMap = new QMap<QString, QString>();
    layout = new QVBoxLayout(this);
    topBar = new QLabel(this);
    topBar->setText(title);
    topBar->setStyleSheet("background-color: #dcdcdc;"
                          "padding-left: 2px");
    topBar->setFixedHeight(25);

    setAcceptDrops(false);

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

    setupEventFilter();

    if(title == "My Videos")
    {
        loadVideosFromFolder();
    }

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
        if(this->title != "My Videos" && this->title != "My Music")
        {
            QAction* addAction = contextMenu.addAction(tr("Ajouter un nouvel élément"));

            connect(addAction, &QAction::triggered, this, [this]() {
                QString filePath = QFileDialog:: getOpenFileName(this,tr("Select Video File"),"",tr("MP4 Files (*.MP4 *.mkv *.avi, *.mov)"));
                if(!filePath.isEmpty())
                {
                    addToTable(filePath);
                }
            });
        }
    } else {

        if (this->title != "Media Library") {
            QAction* copyAction = contextMenu.addAction(tr("Copier dans Media Library"));
            connect(copyAction, &QAction::triggered, this, [this, item]() {
                emit copyItemToMediaLibrary(item);
            });
        }

        QAction* deleteAction = contextMenu.addAction(tr("Supprimer"));
        connect(deleteAction, &QAction::triggered, this, [this, item]() {
            int row = tableWidget->row(item);
            QString title = this->tableWidget->item(row, 0)->text();

            videoPathMap->remove(title);
            tableWidget->removeRow(row);
        });
    }
    contextMenu.exec(tableWidget->viewport()->mapToGlobal(pos));
}

void CustomTable::addToTable(const QString &filePath)
{
    QFileInfo fileInfo(filePath);
    QString title = fileInfo.completeBaseName();
    QString fileExtension = fileInfo.suffix().toLower();

    int currentRow = this->tableWidget->rowCount();
    this->tableWidget->insertRow(currentRow);

    this->tableWidget->setItem(currentRow, 0, new QTableWidgetItem(title));
    this->tableWidget->setItem(currentRow, 1, new QTableWidgetItem("Author"));

    if(fileExtension == "jpg" || fileExtension == "png")
    {
        this->tableWidget->setItem(currentRow, 2, new QTableWidgetItem("00:10"));
    }
    else
    {
        this->tableWidget->setItem(currentRow, 2, new QTableWidgetItem("--:--"));
    }

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

void CustomTable::saveToJSON(const QString &filename) {
    QString dataPath = QCoreApplication::applicationDirPath();
    QDir dir(dataPath);

    if (!dir.exists()) {
        dir.mkpath(".");
    }

    QString filePath = dir.filePath(filename);

    QJsonObject json;
    for (auto it = videoPathMap->constBegin(); it != videoPathMap->constEnd(); ++it) {
        json[it.key()] = it.value();
    }

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        qWarning() << "Impossible d'ouvrir le fichier pour l'écriture:" << filePath;
        return;
    }

    file.write(QJsonDocument(json).toJson());
    file.close();
}

void CustomTable::loadFromJSON(const QString &filename) {
    QString dataPath = QCoreApplication::applicationDirPath();
    QString filePath = dataPath + "/" + filename;

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Impossible d'ouvrir le fichier pour la lecture:" << filePath;
        return;
    }

    QJsonObject json = QJsonDocument::fromJson(file.readAll()).object();
    file.close();

    for (auto it = json.constBegin(); it != json.constEnd(); ++it) {
        addToTable(it.value().toString());
    }
}

void CustomTable::setupEventFilter() {
    tableWidget->viewport()->installEventFilter(this);
}

bool CustomTable::eventFilter(QObject *watched, QEvent *event) {
    if (watched == tableWidget->viewport() && event->type() == QEvent::MouseButtonPress) {
        auto *mouseEvent = static_cast<QMouseEvent *>(event);
        if (mouseEvent->button() == Qt::LeftButton) {
            QPoint pos = mouseEvent->pos();
            if (!tableWidget->itemAt(pos)) {
                tableWidget->clearSelection();
            }
        }
    }
    return QWidget::eventFilter(watched, event);
}

void CustomTable::loadVideosFromFolder() {
    QString videosFolderPath = QStandardPaths::writableLocation(QStandardPaths::MoviesLocation);
    QDir videosFolder(videosFolderPath);
    QStringList videoFiles = videosFolder.entryList(QStringList() << "*.mp4" << "*.mkv" << "*.avi" << "*.mov", QDir::Files);

    foreach (const QString &videoFile, videoFiles) {
        QString filePath = videosFolder.absoluteFilePath(videoFile);
        addToTable(filePath);
    }
}

CustomTable::~CustomTable() {
    delete videoPathMap;
}

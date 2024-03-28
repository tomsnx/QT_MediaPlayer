#ifndef CUSTOMTABLE_H
#define CUSTOMTABLE_H

#include <QWidget>
#include <QTableWidget>
#include <QHeaderView>
#include <QLabel>
#include <QVBoxLayout>
#include <QMenu>
#include <QString>
#include <QFileDialog>
#include <QMediaPlayer>
#include <QTime>
#include <QFileInfo>
#include <QMimeData>
#include <QtMultimediaWidgets>
#include <QtMultimedia>

class CustomTable : public QWidget
{
    Q_OBJECT

signals:
    void itemDoubleClicked(QString filePath);
    void copyItemToMediaLibrary(QTableWidgetItem* item);

public:
    explicit CustomTable(const QString &title, QWidget *parent = nullptr);
    QTableWidget *tableWidget;
    QMap<QString, QString> *videoPathMap;

    void saveToJSON(const QString &filename);
    void loadFromJSON(const QString &filename);
    void addToTable(const QString &filePath);

    ~CustomTable();

private:
    QLabel *topBar;
    QVBoxLayout *layout;
    QString title;

private slots:
    void onItemDoubleClicked(QTableWidgetItem *item);
    void onCustomContextMenuRequested(const QPoint &pos);
};

#endif // CUSTOMTABLE_H

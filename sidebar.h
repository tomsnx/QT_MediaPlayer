#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QWidget>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QTreeView>
#include <QStandardItemModel>
#include <QHeaderView>
#include <QListWidgetItem>
#include <QLabel>
#include <QVBoxLayout>
#include <QTreeWidget>
#include <QListWidget>
#include <QLabel>

#include <videoArea.h>

class SideBar : public QWidget {
    Q_OBJECT

public:
    explicit SideBar(VideoArea *videoArea, QWidget *parent = nullptr);

    QString getCurrentItemText() const;

private slots:
    void handleSelectionChanged(QListWidgetItem *current, QListWidgetItem *previous);

private:
    QScrollArea *scrollArea;
    QVBoxLayout *layout;
    QTreeView *treeView;
    QLabel *spaceLabel;
    QListWidgetItem *item;
    QListWidgetItem *headerItem;
    QListWidget *listWidget;
    VideoArea *videoArea;

    void addSectionHeader(QListWidget *listWidget, const QString &text);
};

#endif // SIDEBAR_H

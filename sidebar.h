#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QWidget>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QTreeView>
#include <QStandardItemModel>
#include <QHeaderView>

class SideBar : public QWidget {
    Q_OBJECT

public:
    explicit SideBar(QWidget *parent = nullptr);

private:
    QScrollArea *scrollArea;
    QVBoxLayout *layout;
    QTreeView *treeView;
};

#endif // SIDEBAR_H

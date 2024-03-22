#include "sideBar.h"

SideBar::SideBar(QWidget *parent) : QWidget(parent) {
    scrollArea = new QScrollArea(this);
    scrollArea->setStyleSheet("background-color: #adacac; color: black;");
    scrollArea->setContentsMargins(0, 0, 0, 0);
    scrollArea->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QWidget *sideBarContent = new QWidget();
    sideBarContent->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sideBarContent->setStyleSheet("background-color: red;");

    layout = new QVBoxLayout(sideBarContent);
    layout->setAlignment(Qt::AlignTop);
    layout->setContentsMargins(0, 0, 0, 0);

    QTreeView *treeView = new QTreeView();
    treeView->header()->setSectionResizeMode(QHeaderView::Stretch);
    treeView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QStandardItemModel *model = new QStandardItemModel();
    model->setHorizontalHeaderLabels(QStringList() << "MY COMPUTER");
    QStandardItem *fileItem = new QStandardItem("File");
    model->appendRow(fileItem);

    treeView->setModel(model);
    treeView->setStyleSheet("QTreeView {"
                            "border: none;"
                            "margin: 0;"
                            "padding: 0;"
                            "}"
                            "QTreeView::item {"
                            "margin: 0;"
                            "padding: 0;"
                            "}");

    // Réglage de la largeur des colonnes pour correspondre à la largeur du QTreeView
    treeView->header()->setStretchLastSection(false);
    treeView->header()->setSectionResizeMode(QHeaderView::Stretch);

    layout->addWidget(treeView);
    scrollArea->setWidget(sideBarContent);

    layout->addWidget(treeView);
    scrollArea->setWidget(sideBarContent);

    scrollArea->setFixedWidth(250);
    scrollArea->setMinimumWidth(100);
    scrollArea->setMaximumWidth(250);
}

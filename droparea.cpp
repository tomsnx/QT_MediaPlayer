#include "DropArea.h"

DropArea::DropArea(QWidget *parent) : QWidget(parent) {
    setAcceptDrops(true);
    this->setStyleSheet("background-color: #f0f0f0;"
                            "QTreeView { border: none; }");
}

void DropArea::dragEnterEvent(QDragEnterEvent *event) {
    if (event->mimeData()->hasFormat("text/plain")) {
        event->acceptProposedAction();
    }
}

void DropArea::dropEvent(QDropEvent *event) {
    event->acceptProposedAction();
}

#ifndef DROPAREA_H
#define DROPAREA_H

#include <QWidget>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>

class DropArea : public QWidget {

public:
    explicit DropArea(QWidget *parent = nullptr);

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;
};

#endif // DROPAREA_H

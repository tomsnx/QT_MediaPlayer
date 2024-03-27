#ifndef CUSTOMLIST_H
#define CUSTOMLIST_H

#include <QListWidget>
#include <QKeyEvent>

class CustomList : public QListWidget {
    Q_OBJECT
public:
    explicit CustomList(QWidget *parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // CUSTOMLIST_H

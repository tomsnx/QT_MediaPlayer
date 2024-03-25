#ifndef BUTTON_H
#define BUTTON_H

#include <QObject>
#include <QPushButton>
#include <QMediaPlayer>
#include <videoArea.h>

class Button : public QPushButton {
    Q_OBJECT
public:
    explicit Button(const QSize &size, const QIcon &icon, QWidget *parent = nullptr, const QString &text = QString());

private slots:
    void onClicked();

private:
    QSize size;
};

#endif // BUTTON_H

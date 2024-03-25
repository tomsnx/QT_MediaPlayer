#include "button.h"

Button::Button(const QSize &size, const QIcon &icon, QWidget *parent, const QString &text)
    : QPushButton(text, parent) {
    setFixedSize(size);
    setIcon(icon);

    connect(this, &QPushButton::clicked, this, [this]() {
        onClicked();
    });
}

void Button::onClicked()
{

}

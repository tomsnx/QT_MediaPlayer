#ifndef MENUBAR_H
#define MENUBAR_H

#include <QObject>
#include <QMenuBar>

class MenuBar : public QMenuBar
{
    Q_OBJECT
public:
    explicit MenuBar(QWidget *parent = nullptr);

private:
    QMenuBar *menuBar;
    QMenu *fileMenu, *audioMenu, *videoMenu, *subtitleMenu;
    QAction *openFolder,
            *newAction,
            *openAction,
            *IncreaseAction,
            *DecreaseAction,
            *MuteAction,
            *sizeAction,
            *colorAction,
            *bkgColorAction;
};
#endif // MENUBAR_H

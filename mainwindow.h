#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSlider>
#include <QLabel>
#include <QStyle>
#include <QDockWidget>
#include <QScrollArea>
#include <QTreeView>
#include <QTreeView>
#include <QStandardItemModel>
#include <QSplitter>
#include <QHeaderView>

#include <menubar.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void onStatusButtonClicked();
    void onStatusSliderValueChanged(int value);
    void onPlayButtonClicked();
    void onPauseButtonClicked();
    void onStopButtonClicked();
    void onNextButtonClicked();
    void onFullScreenClicked();
    void onPreviousButtonClicked();
    void onProgressSliderMoved(int position);

    Ui::MainWindow *ui;
    MenuBar *menuBar;
    QDockWidget *sideBarDock;
    QHBoxLayout *hboxButtons;
    QSlider *progressSlider, *soundSlider;
    QPushButton *playPauseButton, *pauseButton, *stopButton, *nextButton, *previousButton, *fullScreenButton;
    QLabel *currentTimeLabel, *totalTimeLabel;
};
#endif // MAINWINDOW_H

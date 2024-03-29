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
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QToolBar>
#include <QLabel>

#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QDragEnterEvent>
#include <QMimeData>

#include <videoArea.h>
#include <menubar.h>
#include <sidebar.h>
#include <playerbar.h>

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

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:


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

    void handleFileDropped(const QString& filePath);
    void playVideo(const QString &filePath);

    SideBar *sideBar;
    MenuBar *menubar;
    PlayerBar *playerBar;
    QVideoWidget *videoWidget;
    QMediaPlayer *player;
    VideoArea *videoArea;
    Ui::MainWindow *ui;
    MenuBar *menuBar;
    QDockWidget *sideBarDock;
    QHBoxLayout *hboxButtons;
    QVBoxLayout *mainWindowVBox;
    QSlider *progressSlider, *soundSlider;
    QPushButton *playPauseButton, *pauseButton, *stopButton, *nextButton, *previousButton, *fullScreenButton;
    QLabel *currentTimeLabel, *totalTimeLabel;
    QSplitter *splitter;
    QWidget *containerWidget;

    bool isPlaying;
};
#endif // MAINWINDOW_H

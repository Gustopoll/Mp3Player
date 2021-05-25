#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMovie>
#include "listcontrol.h"
#include "directorycontrol.h"
#include "tagcontrol.h"
#include "detailsongcontrol.h"
#include "musiccontrol.h"
#include <QDesktopServices>
#include <QAudioProbe>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_treeDirectory_itemClicked(QTreeWidgetItem *item, int column);
    void on_buttonBackDirectory_clicked();
    void on_ButtonPlay_clicked();
    void on_ButtonClearMarked_clicked();

    void on_treeMainList_itemDoubleClicked(QTreeWidgetItem *item, int column);
    void onMediaStatusChanged(QMediaPlayer::MediaStatus status);
    void on_positionChanged(qint64 position);
    void on_durationChanged(qint64 position);

    void on_ButtonCloseProperty_2_clicked();
    void on_ButtonCloseProperty_clicked();

    void on_treeMainList_itemClicked(QTreeWidgetItem *item, int column);
    void on_sliderSongPositon_sliderMoved(int position);

    void on_ButtonMute_clicked();
    void on_ButtonForward_clicked();
    void on_ButtonBackward_clicked();

    void on_ButtonYoutube_clicked();

    void on_actionDarkMode_triggered();

    void on_actionClose_triggered();

    void slotGetMusicData(QAudioBuffer musicBuffer); //for musicProbe

    void on_ButtonBackToList_clicked();

    void on_pushButton_clicked();

    void on_treeDirectory_itemDoubleClicked(QTreeWidgetItem *item, int column);

private:
    Ui::MainWindow *ui;
    DirectoryControl* Directory;
    ListControl* List;
    //MusicPlayer* Player;
    MusicControl *controlMusic;
    DetailSongControl *DetailControl;
    TagControl* Tag;
    QMediaPlayer* TagPlayer; //for collect tags form songs
    QMediaPlayer* SongPlayer; //for playing songs
    QMediaPlayer* PropertyPlayer; //for property tag
    QAudioProbe* musicProbe;

    QMovie *movieLoading;
    bool isDark = true;
    QPalette oldPalette;
};
#endif // MAINWINDOW_H

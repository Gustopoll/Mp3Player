#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMediaPlayer>

#include "drawingwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Directory = new DirectoryControl(ui->treeDirectory);
    Directory->Update();

    ui->ButtonClearMarked->setVisible(false);
    ui->treeDirectory->setColumnWidth(2,50);
     ui->treeMainList->setColumnWidth(0,50);
    SongPlayer = new QMediaPlayer(this);
    TagPlayer = new QMediaPlayer(this);
    PropertyPlayer = new QMediaPlayer(this);
    musicProbe = new QAudioProbe();
    musicProbe->setSource(SongPlayer);

    connect(PropertyPlayer, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), this, SLOT(onMediaStatusChanged(QMediaPlayer::MediaStatus)));
    connect(TagPlayer, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), this, SLOT(onMediaStatusChanged(QMediaPlayer::MediaStatus)));
    connect(SongPlayer,&QMediaPlayer::positionChanged, this,&MainWindow::on_positionChanged);
    connect(SongPlayer,&QMediaPlayer::durationChanged, this,&MainWindow::on_durationChanged);
    connect(musicProbe, SIGNAL(audioBufferProbed(QAudioBuffer)), this, SLOT(slotGetMusicData(QAudioBuffer)));

    Tag = new TagControl(TagPlayer);
    List = new ListControl(ui->treeMainList,Tag);
    controlMusic = new MusicControl(SongPlayer,List);

    DetailControl = new DetailSongControl(controlMusic->player);

    movieLoading = new QMovie(":/Images/images/loader.gif");
    ui->labelLoading->setMovie(movieLoading);
    ui->labelLoading->show();
    on_actionDarkMode_triggered();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::slotGetMusicData(QAudioBuffer buffer)
{
    quint16 *data = buffer.data<quint16>();
    ui->widget->SetData(data);

}

void MainWindow::onMediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    if (status == QMediaPlayer::MediaStatus::LoadedMedia)
    {
        if (TagPlayer == QObject::sender())
            List->TagSong();

        if (PropertyPlayer == QObject::sender())
        {
            Tag->GetTags(ui->treePropertyList,PropertyPlayer);
            ui->DirectoryPages->setCurrentIndex(1);
        }
        return;
    }
    if (status == QMediaPlayer::MediaStatus::InvalidMedia)
    {
        List->TagSong();
        return;
    }
}

void MainWindow::on_positionChanged(qint64 position)
{
    ui->sliderSongPositon->setValue(position);
    int seconds = (position/1000) % 60;
    int minutes = (position/60000) % 60;
    ui->labelTimeLeft->setText(QString::number(minutes) + ":" + QString::number(seconds));
}

void MainWindow::on_durationChanged(qint64 position)
{
    ui->sliderSongPositon->setMaximum(position);
    int seconds = (position/1000) % 60;
    int minutes = (position/60000) % 60;
    ui->labelTimeTotal->setText(QString::number(minutes) + ":" + QString::number(seconds));
}

void MainWindow::on_treeDirectory_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    ui->treeMainList->setSortingEnabled(false);
    //foreach (auto dir,Directory->MarkedDirs) //open all marked dirs
      //  qDebug() << dir;

    if (column != 2)
    {
        Directory->Open(item->text(0));
        Directory->Update();
        if (Directory->MarkedDirs.isEmpty() == true)
            List->ShowList(Directory->directory);

        ui->treeMainList->sortByColumn(0, Qt::AscendingOrder);
        ui->treeMainList->setSortingEnabled(true);
        return;
    }
}


void MainWindow::on_treeDirectory_itemClicked(QTreeWidgetItem *item, int column)
{
    if (column != 2)
        return;

    if (item->checkState(2) == Qt::CheckState::Checked)
        Directory->MarkDirectory(item->text(0));
    else
        Directory->UnmarkDirectory(item->text(0));

    if (Directory->MarkedDirs.isEmpty() == true)
        ui->ButtonClearMarked->setVisible(false);
    else
    {
        ui->ButtonClearMarked->setVisible(true);
    }
    ui->ButtonClearMarked->setText("Unmarked " + QString::number(Directory->MarkedDirs.size()));
    int i = 0;
    List->Clear();
    foreach (auto dir,Directory->MarkedDirs) //open all marked dirs
    {
        i = List->ShowMultipleLists(dir,i);
    }
}

void MainWindow::on_buttonBackDirectory_clicked()
{
    Directory->Back();
    Directory->Update();
}

void MainWindow::on_ButtonPlay_clicked()
{
    auto item = ui->treeMainList->selectedItems();
    if (item.isEmpty() == true)
    {
        auto firstitem = ui->treeMainList->itemAt(0,0);
        if (firstitem != nullptr)
        {
            firstitem->setSelected(true);
        }
    }


   bool status = controlMusic->Play(ui->ButtonPlay);
   if (status == true)
   {
    DetailControl->SetImage(ui->labelSongSmallImage);
    DetailControl->SetProperty(ui->listPlayingSong);
    ui->ActualSongStack->setCurrentIndex(1);
    ui->PlayingStats->setCurrentIndex(1);
   }

}

void MainWindow::on_ButtonClearMarked_clicked()
{
    Directory->MarkedDirs.clear();
    Directory->Update();
    ui->ButtonClearMarked->setVisible(false);
    List->ShowList(Directory->directory);
}

void MainWindow::on_treeMainList_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    int index = item->text(0).toInt()-1;
    controlMusic->Play(List->list[index],ui->ButtonPlay);
    DetailControl->SetImage(ui->labelSongSmallImage);
    DetailControl->SetProperty(ui->listPlayingSong);
    ui->ActualSongStack->setCurrentIndex(1);
    ui->PlayingStats->setCurrentIndex(1);
    ui->labelTimeLeft->setText("0:0");
    ui->labelTimeTotal->setText("0:0");
    Q_UNUSED(column);
}

void MainWindow::on_ButtonCloseProperty_2_clicked()
{

    ui->DirectoryPages->setCurrentIndex(0);
}

void MainWindow::on_ButtonCloseProperty_clicked()
{
    ui->DirectoryPages->setCurrentIndex(0);
}

void MainWindow::on_treeMainList_itemClicked(QTreeWidgetItem *item, int column)
{
    int index = item->text(0).toInt()-1;
    QString path = List->list[index].Path + "/" + item->text(1);
    movieLoading->start();
    ui->DirectoryPages->setCurrentIndex(2);
    PropertyPlayer->setMedia(QUrl::fromLocalFile(path));
    Q_UNUSED(column);
}

void MainWindow::on_sliderSongPositon_sliderMoved(int position)
{
    SongPlayer->setPosition(position);

}

void MainWindow::on_ButtonMute_clicked()
{
    static bool isClicked = true;
    QString ovalButton = "border-style: solid; border-width:1px; max-width:30px; max-height:30px; min-width:30px; min-height:30px;";
    if (isClicked == true)
    {
        ui->ButtonMute->setStyleSheet("border-image:  url(:/Images/images/unmute.png);" + ovalButton); //change image to play
        SongPlayer->setMuted(true);
        isClicked = false;
    }
    else
    {
        ui->ButtonMute->setStyleSheet("border-image:  url(:/Images/images/mute.png);" + ovalButton); //change image to pause
        SongPlayer->setMuted(false);
        isClicked = true;
    }
}

void MainWindow::on_ButtonForward_clicked()
{
    auto item = ui->treeMainList->selectedItems();
    if (item.isEmpty() == true)
        return;
    auto itemBelow = ui->treeMainList->itemBelow(item[0]);
    if (itemBelow == nullptr)
        return;
    on_treeMainList_itemDoubleClicked(itemBelow,0);
    itemBelow->setSelected(true);
    item[0]->setSelected(false);
}

void MainWindow::on_ButtonBackward_clicked()
{
    auto item = ui->treeMainList->selectedItems();
    if (item.isEmpty() == true)
        return;
    auto itemAbove = ui->treeMainList->itemAbove(item[0]);
    if (itemAbove == nullptr)
        return;
    on_treeMainList_itemDoubleClicked(itemAbove,0);
    itemAbove->setSelected(true);
    item[0]->setSelected(false);
}



void MainWindow::on_ButtonYoutube_clicked()
{
    QString link = "https://www.youtube.com/results?search_query=";
    auto item = ui->treeMainList->selectedItems();
    if (item.isEmpty() == true)
        return;
    if ((item[0]->text(2) != "") && (item[0]->text(3) != ""))
    {
        auto author = item[0]->text(3);
        auto song = item[0]->text(2);
        QDesktopServices::openUrl(QUrl(link + author + "+" + song));
    }
    else
        QDesktopServices::openUrl(QUrl(link + item[0]->text(1)));

}

void MainWindow::on_actionDarkMode_triggered()
{
    if (isDark == false)
    {
        QString pattern = "background-color: rgb(30, 30, 30) ; color: rgb(255, 255, 255);";
        QString header = " QHeaderView::section{background-color: rgb(30, 30, 30);} border-color: color: rgb(30, 30, 30);";
        QString line = " border:0px;";
        QPalette palette;
        palette.setColor(QPalette::Window, QColor(10, 10, 10)); //40
        oldPalette = qApp->palette();
        qApp->setPalette(palette);
        qApp->setStyleSheet("QToolTip { background-color: rgb(30, 30, 30) ; color: rgb(255, 255, 255);}");
        ui->menuDark->setStyleSheet(pattern);
        ui->statusbar->setStyleSheet(pattern);
        ui->listPlayingSong->setStyleSheet(pattern + line);
        ui->treeMainList->setStyleSheet(header + line);
        ui->PlaylistPages->setStyleSheet(pattern + line);
        ui->treePropertyList->setStyleSheet(pattern + line);
        ui->DirectoryPages->setStyleSheet(pattern + line);
        ui->labelTimeLeft->setStyleSheet("color: rgb(255, 255, 255);");
        ui->labelTimeTotal->setStyleSheet("color: rgb(255, 255, 255);");
        isDark = true;
    }
    else
    {
        qApp->setPalette(oldPalette);
        qApp->setStyleSheet("");
        ui->statusbar->setStyleSheet("");
        ui->menuDark->setStyleSheet("");
        ui->listPlayingSong->setStyleSheet("border:0px;");
        ui->treeMainList->setStyleSheet("border:0px;");
        ui->PlaylistPages->setStyleSheet("border:0px;");
        ui->treePropertyList->setStyleSheet("border:0px;");
        ui->DirectoryPages->setStyleSheet("border:0px; background-color: rgb(255, 255, 255);");
        ui->labelTimeLeft->setStyleSheet("");
        ui->labelTimeTotal->setStyleSheet("");
        isDark = false;
    }
}

void MainWindow::on_actionClose_triggered()
{
    QCoreApplication::quit();
}

void MainWindow::on_ButtonBackToList_clicked()
{
    ui->PlaylistPages->setCurrentIndex(0);
}

void MainWindow::on_pushButton_clicked()
{
    ui->PlaylistPages->setCurrentIndex(1);
}


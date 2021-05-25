#include "tagcontrol.h"

TagControl::TagControl( QMediaPlayer *player)
{
    this->player = player;
}

Song TagControl::GetTags()
{
    auto data = player->availableMetaData();
    edittingSong.Artist = "";
    edittingSong.Album = "";
    edittingSong.Year = 0;
    foreach (auto d, data)
    {
        if (d== "Title")
            edittingSong.Title = player->metaData(d).toString();
        if (d == "Author")
            edittingSong.Artist = player->metaData(d).toString();
        if (d == "AlbumTitle")
            edittingSong.Album = player->metaData(d).toString();
        if (d == "Year")
            edittingSong.Year = player->metaData(d).toInt();
        if (d == "ThumbnailImage")
        {
            edittingSong.Image = player->metaData(d).value<QImage>();
        }
    }
    return edittingSong;
}

void TagControl::GetTags(QTreeWidget* list, QMediaPlayer *p)
{
    auto data = p->availableMetaData();
    list->clear();
    QList<QString> NoShowTags = {"PeakValue","AverageLevel","SampleRate","AudioBitRate","ThumbnailImage","ChannelCount"};

    foreach (auto d, data)
    {
        QTreeWidgetItem* item = new QTreeWidgetItem();
        item->setText(0,d);
        if (d == "Duration")
        {
            int duration = p->metaData(d).toInt();
            int seconds = (duration/1000) % 60;
            int minutes = (duration/60000) % 60;
            item->setText(1,QString::number(minutes) + ":" + QString::number(seconds));
            list->addTopLevelItem(item);
            continue;
        }
        if (NoShowTags.contains(d) == true)
            continue;

        item->setText(1,p->metaData(d).toString());
        list->addTopLevelItem(item);
    }
}

void TagControl::StartTagging(Song song)
{
    index = 0;
    edittingSong = song;
    player->setMedia(QUrl::fromLocalFile(song.Path + "/" + song.Name));
}

void TagControl::NextSong(Song song)
{
    edittingSong = song;
    player->setMedia(QUrl::fromLocalFile(song.Path + "/" + song.Name));
    index++;
}

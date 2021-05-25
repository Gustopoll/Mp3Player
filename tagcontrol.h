#ifndef TAGCONTROL_H
#define TAGCONTROL_H

#include <QMediaPlayer>
#include <QTreeWidget>
#include "song.h"

class TagControl
{
public:
    TagControl( QMediaPlayer *player);

    QMediaPlayer *player;
    int index = 0;
    Song edittingSong;

    void StartTagging(Song song);
    Song GetTags();
    void GetTags(QTreeWidget* list, QMediaPlayer *p);
    void NextSong(Song song);
};

#endif // TAGCONTROL_H

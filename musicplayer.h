#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <QString>
#include <QMediaPlayer>
#include <QMediaMetaData>
#include "song.h"
#include "listcontrol.h"

class MusicPlayer
{
public:
    MusicPlayer(QMediaPlayer *player, ListControl *list);

    QMediaPlayer *player;
    ListControl *list;
    Song playingSong;

    void Play(QString path);
    void Play(Song song);
};

#endif // MUSICPLAYER_H

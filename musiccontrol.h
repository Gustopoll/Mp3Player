#ifndef MUSICCONTROL_H
#define MUSICCONTROL_H

#include <QPushButton>
#include "musicplayer.h"
//#include "song.h"


class MusicControl
{
public:
    MusicControl(QMediaPlayer *player, ListControl *list);

    MusicPlayer *player;
    bool isPlaying = false;

    void Play(Song song, QPushButton *button);
    bool Play(QPushButton *button);
    void Pause(QPushButton *button);
};

#endif // MUSICCONTROL_H

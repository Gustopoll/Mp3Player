#ifndef DETAILSONGCONTROL_H
#define DETAILSONGCONTROL_H

#include <QLabel>
#include <QListWidget>
#include "musicplayer.h"

class DetailSongControl
{
public:
    DetailSongControl(MusicPlayer *control);

    MusicPlayer *musicPlayer;

    void SetImage(QLabel *label);
    void SetProperty(QListWidget *widget);
};

#endif // DETAILSONGCONTROL_H

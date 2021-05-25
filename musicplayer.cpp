#include "musicplayer.h"

MusicPlayer::MusicPlayer(QMediaPlayer *player, ListControl *list)
{
    this->player = player;
    this->list = list;
}

void MusicPlayer::Play(QString path)
{
    player->setMedia(QUrl::fromLocalFile(path));
    player->setVolume(50);
    player->play();
}

void MusicPlayer::Play(Song song)
{
    this->playingSong = song;
    QString path = song.Path + "/" + song.Name;
    qDebug() << "Playing on: " << path;
    player->setMedia(QUrl::fromLocalFile(path));
    player->setVolume(50);
    player->play();

}


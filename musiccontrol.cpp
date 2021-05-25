#include "musiccontrol.h"

MusicControl::MusicControl(QMediaPlayer *player, ListControl *list)
{
    this->player = new MusicPlayer(player,list);
}

void MusicControl::Play(Song song, QPushButton *button)
{
    player->Play(song);
    QString ovalButton = "border-style: solid; border-width:1px; max-width:100px; max-height:100px; min-width:100px; min-height:100px;";
    button->setStyleSheet("border-image:  url(:/Images/images/PlayT.png);" + ovalButton); //change image to play
    isPlaying = true;
}


bool MusicControl::Play(QPushButton *button)
{
    if (isPlaying == true)
    {
        Pause(button);
        return false;
    }

    if (player->list->list.isEmpty() == true )
        return false;
    if (player->player->isAudioAvailable() == true)
    {
        player->player->play(); //continue playing
        QString ovalButton = "border-style: solid; border-width:1px; max-width:100px; max-height:100px; min-width:100px; min-height:100px;";
        button->setStyleSheet("border-image:  url(:/Images/images/PlayT.png);" + ovalButton); //change image to play
        isPlaying = true;
    }
    else //if no song playing and direcotry of list is open
    {
         Play(player->list->list[0],button); //play first song in list
    }
    return true;
}

void MusicControl::Pause(QPushButton *button)
{
    isPlaying = false;
    player->player->pause();
    QString ovalButton = "border-style: solid; border-width:1px; max-width:100px; max-height:100px; min-width:100px; min-height:100px;";
    button->setStyleSheet("border-image:  url(:/Images/images/PauseT.png);" + ovalButton); //change image to pause
}


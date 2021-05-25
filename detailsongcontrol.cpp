#include "detailsongcontrol.h"

DetailSongControl::DetailSongControl(MusicPlayer *control)
{
    this->musicPlayer = control;
}

void DetailSongControl::SetImage(QLabel *label)
{
    QImage img(":/Images/images/NoSong.png");
    if (musicPlayer->playingSong.Image.isNull() == false)
    {
        img = musicPlayer->playingSong.Image;
    }
    label->setPixmap(QPixmap().fromImage(img));
    label->setScaledContents(true);
}

void DetailSongControl::SetProperty(QListWidget* widget)
{
    widget->clear();
    widget->addItem(musicPlayer->playingSong.Name);
    widget->addItem(musicPlayer->playingSong.Title);
    widget->addItem(musicPlayer->playingSong.Artist);
}

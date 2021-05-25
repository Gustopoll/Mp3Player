#ifndef SONG_H
#define SONG_H
#include <QString>
#include <QImage>

class Song
{
public:

    Song();
    Song(QString name, QString path);

    QString Name;
    QString Path;

    QString Title;
    QString Artist;
    QString Album;
    int Year;

    QImage Image;

};

#endif // SONG_H

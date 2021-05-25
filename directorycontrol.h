#ifndef LISTCONTROL_H
#define LISTCONTROL_H
#include <QTreeWidget>
#include <QDir>
#include <QDebug>
#include "mytreewidget.h"

class DirectoryControl
{
public:
    DirectoryControl(QTreeWidget* list);

    QTreeWidget* list;
    QDir directory;

    QVector<QString> MarkedDirs; //Absolute Path of directory
    //true if directory is root else false
    bool Root = false;

public:
    void AddItem(QString NameDir, int CountSongs);
    void Update();
    void Open(QString path);
    void Back();
    void MarkDirectory(QString dir);
    void UnmarkDirectory(QString dir);


    //return number of mp3 on path
    int SongCount(QString path);
};

#endif // LISTCONTROL_H

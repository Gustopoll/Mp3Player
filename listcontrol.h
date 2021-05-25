#ifndef TREELISTCONTROL_H
#define TREELISTCONTROL_H
#include <QTreeWidget>
#include <QDir>
#include "song.h"
#include "tagcontrol.h"
#include "mytreewidget.h"

class ListControl
{
public:
    ListControl(QTreeWidget* tree, TagControl *tagplayer);

    QTreeWidget* tree;
    QVector<Song> list;
    TagControl* tag;

    void AddItem(int i, QString name, QString title, QString singer,QString album, int year, QString path);
    void DeleteItem(QString name);
    void Clear();

    bool ShowList(QDir dir);
    int ShowMultipleLists(QDir dir, int position); //return numbers of given elment into list
    void TagSong();
    bool tagging = false;

};

#endif // TREELISTCONTROL_H

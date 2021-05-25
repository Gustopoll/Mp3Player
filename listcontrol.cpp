#include "listcontrol.h"

ListControl::ListControl(QTreeWidget* tree, TagControl *tagplayer)
{
    this->tree = tree;
    this->tag = tagplayer;
}

void ListControl::AddItem(int i,QString name, QString title, QString singer,QString album, int year, QString path)
{
    MyTreeWidget* item = new MyTreeWidget();
    item->setText(0,QString::number(i));
    item->setText(1,name);
    item->setText(2,title);
    item->setText(3,singer);
    item->setText(4,album);
    if (year != 0)
        item->setText(5,QString::number(year));
    tree->addTopLevelItem(item);

    Song song(name,path);
    list.append(song);
}

void ListControl::DeleteItem(QString name)
{
    auto items = tree->findItems(name,0,1);
    foreach(auto item, items)
    {
        tree->removeItemWidget(item,0);
        tree->removeItemWidget(item,1);
        tree->removeItemWidget(item,2);
        tree->removeItemWidget(item,3);
        tree->removeItemWidget(item,4);
        tree->removeItemWidget(item,5);
    }
}

void ListControl::Clear()
{
    tree->clear();
    list.clear();
}

bool ListControl::ShowList(QDir dir)
{
    Clear();
    QStringList file = dir.entryList(QStringList() << "*.mp3" << "*.wav" << "*.wma" ,QDir::Files);
    if (file.isEmpty() == true)
        return false;
    int i = 0;
    foreach(QString filename, file) {
        i++;
        AddItem(i, filename,"","","",0,dir.absolutePath());
    }

    tagging = true;
    tag->StartTagging(list[0]);
    return true;
}

int ListControl::ShowMultipleLists(QDir dir, int position)
{
    QStringList file = dir.entryList(QStringList() << "*.mp3" << "*.aac" << "*.flac" << "*.wav" << "*.wma" ,QDir::Files);
    if (file.isEmpty() == true)
        return position;
    foreach(QString filename, file) {
        position++;
        AddItem(position, filename,"","","",0,dir.absolutePath());
    }

    tagging = true;
    tag->StartTagging(list[0]);
    return position;
}

void ListControl::TagSong()
{
    if (tagging == false)
        return;

   list[tag->index] = tag->GetTags();

   auto item = tree->topLevelItem(tag->index);
   item->setText(2,list[tag->index].Title);
   item->setText(3,list[tag->index].Artist);
   item->setText(4,list[tag->index].Album);
   if (list[tag->index].Year != 0)
        item->setText(5,QString::number(list[tag->index].Year));

   if (tag->index+1 == list.length())
   {
        tagging = false;
        tag->index = 0;
        return;
   }
   tag->NextSong(list[tag->index+1]);
}


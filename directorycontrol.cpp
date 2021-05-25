#include "directorycontrol.h"

DirectoryControl::DirectoryControl(QTreeWidget* list)
{
    this->list = list;
    Root = true;
}


void DirectoryControl::AddItem(QString NameDir, int CountSongs)
{
    QTreeWidgetItem* item = new QTreeWidgetItem();
    item->setFlags(item->flags() | Qt::ItemIsUserCheckable | Qt::ItemIsSelectable);
    item->setText(0,NameDir);
    item->setText(1,QString::number(CountSongs));

    QString temp = directory.absolutePath() + NameDir;
    if (directory.isRoot() == false)
        temp = directory.absolutePath() + "/"+ NameDir;

    if (MarkedDirs.contains(temp) == true)
        item->setCheckState(2,Qt::Checked);
    else
        item->setCheckState(2,Qt::Unchecked);

    list->addTopLevelItem(item);
}


void DirectoryControl::Update()
{
    list->clear();

    if (Root == false)
    {
        QStringList file = directory.entryList(QStringList(),QDir::Dirs);
        foreach(QString filename, file) {
            if ((filename == ".") || (filename == ".."))
                continue;
            int count = SongCount(filename);
            AddItem(filename,count);
        }
    }
    else
    {
        QDir dir;
        foreach(QFileInfo item, dir.drives() )
        {
            QString filename = item.absoluteFilePath();
            int count = SongCount(filename);
            AddItem(filename,count);
        }
    }
}

void DirectoryControl::Open(QString path)
{
    if (Root == false)
    {
        directory.cd("./" + path);
    }
    else //if changing root directory
    {
        auto dir = QDir(path);
        directory.swap(dir);
        Root = false;
    }
}


void DirectoryControl::Back()
{
   if (directory.cd("..") == false)
       Root = true;
}

int DirectoryControl::SongCount(QString path)
{

    auto tmp = directory;
    directory.cd(path);
    int cnt = 0;
    QStringList file = directory.entryList(QStringList() << "*.mp3" << "*.wav" << "*.wma", QDir::Files);
    foreach(QString filename, file) {
        cnt++;
    }
    directory = tmp;
    return cnt;
}

void DirectoryControl::MarkDirectory(QString dir)
{
    if (directory.isRoot() == true)
        MarkedDirs.append(directory.absolutePath() + dir);
    else
        MarkedDirs.append(directory.absolutePath() + "/" + dir);
}

void DirectoryControl::UnmarkDirectory(QString dir)
{
    QString path = directory.absolutePath();
    if (directory.isRoot() == true)
        path += dir;
    else
        path +="/"+ dir;

    int i = 0;
    foreach (QDir d, MarkedDirs)
    {
        if (d == path)
        {
            MarkedDirs.remove(i);
            break;
        }
        i++;
    }
}

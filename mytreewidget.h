#ifndef MYTREEWIDGET_H
#define MYTREEWIDGET_H

#include <QTreeWidget>
#include <QHeaderView>

class MyTreeWidget : public QObject, public QTreeWidgetItem
{
    Q_OBJECT

public:
    MyTreeWidget(QTreeWidget* parent = 0);
    bool operator<(const QTreeWidgetItem &other) const override;
};


#endif // MYTREEWIDGET_H

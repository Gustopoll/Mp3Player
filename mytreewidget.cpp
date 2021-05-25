#include "mytreewidget.h"
#include <QString>
#include <QTreeWidgetItem>
#include <QtDebug>


MyTreeWidget::MyTreeWidget(QTreeWidget *parent) : QTreeWidgetItem(parent)
{

}

bool MyTreeWidget::operator<(const QTreeWidgetItem &other) const
{
    Q_ASSERT( other.treeWidget() == treeWidget() );
    if (treeWidget()->sortColumn() != 0)
    {
        int sortCol = treeWidget()->sortColumn();
        QString val = text(sortCol);
        QString otherVal = other.text(sortCol);
        return val < otherVal;
    }
    else
    {
        const int col = treeWidget()->sortColumn();
        const int role = Qt::DisplayRole;
        return( data( col, role ).toInt() < other.data( col, role ).toInt() );
    }
}


#include "drawingwidget.h"
#include <QtDebug>

DrawingWidget::DrawingWidget(QWidget *parent) : QWidget(parent)
{

}


void DrawingWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPen pen;
    pen.setWidth(3);
    painter.setPen(pen);
    int maxValue = 65535;
    int height = this->size().height()-1;
    int numberOfColumn = 50;
    int size = this->size().width()/numberOfColumn;
    for (int i = 0; i < numberOfColumn; i++)
    {
        int value = (data[i]/(1.0 * maxValue))*height;
        painter.fillRect(size*i,height-value,(size)*i+size,height-value,QBrush(Qt::red));
    }
    Q_UNUSED(event);
}

void DrawingWidget::SetData(quint16 *value)
{

    for (int i = 0; i < 50; i++)
    {

        if (value[i] < 32766)
            data[i] = value[i];
        else
            data[i] = 0;
    }

    update();
}

#ifndef DRAWINGWIDGET_H
#define DRAWINGWIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>

class DrawingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DrawingWidget(QWidget *parent = nullptr);

    virtual void paintEvent(QPaintEvent *event);
    void SetData(quint16 *data);
    quint16 data[50];
signals:

};

#endif // DRAWINGWIDGET_H

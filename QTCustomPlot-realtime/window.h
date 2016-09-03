#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWindow>
#include "qcustomplot.h"

class Window : public QWidget
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = 0);
    ~Window();

private slots:
    void realtimeDataSlot();

private:
    QCustomPlot *customPlot;
    QTimer dataTimer;
};

#endif // MAINWINDOW_H

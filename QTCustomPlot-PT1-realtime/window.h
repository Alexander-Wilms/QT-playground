#ifndef WINDOW_H
#define WINDOW_H

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
    QVector<double> x, y; // initialize with entries 0..100
    double e;
    double T1;
    double T;
    double kp;
    double oldvalue;
};

#endif // WINDOW_H

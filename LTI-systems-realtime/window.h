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
    void update();

private:
    QCustomPlot *customPlot;
    QTimer dataTimer;
    QVector<double> x, y; // initialize with entries 0..100
    double e;
    double T1;
    double T;
    double kp;
    double out_k_minus_1_PT1 = 0;
    double out_k_minus_1_PT2 = 0;
    double out_k_minus_2_PT2 = 0;
    double PT1(double out_k_minus_1);
    double PT2(double out_k_minus_1, double out_k_minus_2);
};

#endif // WINDOW_H

#ifndef WINDOW_H
#define WINDOW_H

#include <QWindow>
#include "qcustomplot.h"
#include <vector>

class Window : public QWidget
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = 0);
    ~Window();

private slots:
    void update();

private:
    QCustomPlot *cartesian_plot;
    QCPCurve *cartesian_curve;
    QCustomPlot *config_space_plot;
    QCPCurve *curve_in_config_space;
    QCustomPlot *q1_graph;
    QCustomPlot *q2_graph;
    QTimer dataTimer;
    QVector<double> x, y; // initialize with entries 0..100
    double e;
    double T1;
    double T;
    double kp;
    double out_k_minus_1;
    double PT1(double out_k_minus_1);
    std::vector<double> x_values;
    std::vector<double> y_values;
    std::vector<double> inverse_kinematics(double x, double y, double l1, double l2);
    QCPItemLine *link_1;
};

#endif // WINDOW_H

#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QGridLayout>
#include "qcustomplot.h"
#include <QVector>

class Window : public QWidget
{
    Q_OBJECT

public:
    Window(QWidget *parent = 0);
    ~Window();

private:
    QCustomPlot *customPlot;
    QGridLayout *grid;
    double frequency = 1;
    double amplitude = 1;
    double phase = 0;
    void update_graph();
    QVector<double> x, y;

private slots:
    void slot_decrease_amplitude();
    void slot_increase_amplitude();
    void slot_decrease_frequency();
    void slot_increase_frequency();
    void slot_decrease_phase();
    void slot_increase_phase();
};

#endif // WINDOW_H

#include "window.h"

Window::Window(QWidget *parent) :
 QWidget(parent)
{
    setWindowTitle("My first QTCustomPlot");
    setFixedSize(500,500);

    customPlot = new QCustomPlot(this);
    customPlot->setSizePolicy(QSizePolicy ::Expanding , QSizePolicy ::Expanding);
    customPlot->setMinimumHeight(500);
    customPlot->setMinimumWidth(500);
    // generate some data:
    QVector<double> x(101), y(101); // initialize with entries 0..100
    y[0] = 0;
    double e[101] = {0};
    double T1 = 10;
    double T = 1;
    double kp = 1;
    for (int i=1; i<101; ++i)
    {
        x[i] = i/100.0;
        e[i] = 1;
        // discrete PT1
        y[i] = (T1/(T1+T))*y[i-1] + kp*(T/(T1+T))*e[i];
    }

    // create graph and assign data to it:
    customPlot->addGraph();
    customPlot->graph(0)->setData(x, y);
    // give the axes some labels:
    customPlot->xAxis->setLabel("x");
    customPlot->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    customPlot->xAxis->setRange(0, 1);
    customPlot->yAxis->setRange(0, 1);
    customPlot->replot();
}

Window::~Window()
{

}

#include "window.h"

double oldvalue = 0;

Window::Window(QWidget *parent) :
 QWidget(parent)
{
    setWindowTitle("LTI systems - realtime");
    setFixedSize(500,500);

    customPlot = new QCustomPlot(this);
    customPlot->setSizePolicy(QSizePolicy ::Expanding , QSizePolicy ::Expanding);
    customPlot->setMinimumHeight(500);
    customPlot->setMinimumWidth(500);

    // create graph and assign data to it:
    customPlot->addGraph();
    customPlot->addGraph();

    customPlot->graph(1)->setPen(QPen(Qt::red));

    // give the axes some labels:
    customPlot->xAxis->setLabel("x");
    customPlot->yAxis->setLabel("y");

    // set axes ranges, so we see all data:
    customPlot->xAxis->setRange(0, 1);
    customPlot->yAxis->setRange(0, 3.5);

    // connect timer's timeout signal with update() slot
    connect(&dataTimer, SIGNAL(timeout()), this, SLOT(update()));

    // start timer with 10 ms interval
    dataTimer.start(10);
}

void Window::update(void)
{
  // calculate two new data points:

  double t = QDateTime::currentDateTime().toMSecsSinceEpoch()/10;

  static double starttime = t;

  t -= starttime;

  static double last_t = 0;
  double out_k_PT1 = 0;
  double out_k_PT2 = 0;

  if (t-last_t > 0.01) // at most add point every 10 ms
  {

    out_k_PT1 = PT1(out_k_minus_1_PT1);
    out_k_PT2 = PT2(out_k_minus_1_PT2, out_k_minus_2_PT2);

    out_k_minus_1_PT1 = out_k_PT1;

    out_k_minus_2_PT2 = out_k_minus_1_PT2;
    out_k_minus_1_PT2 = out_k_PT2;

    // add data to lines:
    customPlot->graph(0)->addData(t, out_k_PT1);
    customPlot->graph(0)->rescaleKeyAxis();
    //customPlot->graph(0)->rescaleValueAxis();

    customPlot->graph(1)->addData(t, out_k_PT2);
    customPlot->graph(1)->rescaleKeyAxis();
    //customPlot->graph(1)->rescaleValueAxis();

    last_t = t;
  }
  customPlot->replot();
}

double Window::PT1(double out_k_minus_1) {
    double T_sample = 0.01;
    double T = 1;
    double K = 2;
    double stepvalue = 1;

    return (T*-out_k_minus_1/T_sample-K*stepvalue)/(-T/T_sample-1);
}

double Window::PT2(double out_k_minus_1, double out_k_minus_2) {
    double T_sample = 0.01;
    double T = 1;
    double D = 0.2;
    double K = 2;
    double stepvalue = 1;

    return (1/pow(T,2)*(-2*out_k_minus_1+out_k_minus_2)/pow(T_sample,2)+2*D*T*-out_k_minus_1/T_sample-K*stepvalue)/(-pow(T,2)/pow(T_sample,2)-2*D*T/T_sample-1);
}

Window::~Window()
{

}

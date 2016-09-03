#include "window.h"

Window::Window(QWidget *parent) :
 QWidget(parent)
{
    setWindowTitle("My first QTCustomPlot - realtime");
    setFixedSize(500,500);

    customPlot = new QCustomPlot(this);
    customPlot->setSizePolicy(QSizePolicy ::Expanding , QSizePolicy ::Expanding);
    customPlot->setMinimumHeight(500);
    customPlot->setMinimumWidth(500);

    // create graph and assign data to it:
    customPlot->addGraph();
    //customPlot->graph(0)->setData(x, y);
    // give the axes some labels:
    customPlot->xAxis->setLabel("x");
    customPlot->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    customPlot->xAxis->setRange(0, 1);
    customPlot->yAxis->setRange(0, 2);
    customPlot->replot();

    connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
    dataTimer.start(10);
}
double oldvalue = 0;
void Window::realtimeDataSlot(void)
{
  // calculate two new data points:

  double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/10;
  //printf("%f", key);
  static double starttime = key;
  //printf(" ,%f", starttime);
  key -= starttime;
  printf("\n k: %f, ", key);
  double T = 0.01;
  double T1 = 1;
  double kp = 2;
  static double lastPointKey = 0;
  double value0 = 0;
  if (key-lastPointKey > 0.01) // at most add point every 10 ms
  {
    printf("y(k-1): %f, ", oldvalue);
    value0 = (T1/(T1+T))*oldvalue + kp*(T/(T1+T))*1;
    printf("y(k): %f", value0);
     oldvalue = value0;
    // add data to lines:
    customPlot->graph(0)->addData(key, value0);
    customPlot->graph(0)->rescaleKeyAxis();
    lastPointKey = key;
  }
  customPlot->replot();
}


Window::~Window()
{

}

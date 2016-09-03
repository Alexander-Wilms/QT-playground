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
    customPlot->yAxis->setRange(0, 1);
    customPlot->replot();

    connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
    dataTimer.start(0); // Interval 0 means to refresh as fast as possible
}

void Window::realtimeDataSlot(void)
{
  // calculate two new data points:

  double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;

  static double lastPointKey = 0;
  if (key-lastPointKey > 0.01) // at most add point every 10 ms
  {
    double value0 = qSin(key); //qSin(key*1.6+qCos(key*1.7)*2)*10 + qSin(key*1.2+0.56)*20 + 26;
    // add data to lines:
    customPlot->graph(0)->addData(key, value0);
    // remove data of lines that's outside visible range:
    customPlot->graph(0)->removeDataBefore(key-8);
    // rescale value (vertical) axis to fit the current data:
    customPlot->graph(0)->rescaleValueAxis();
    lastPointKey = key;
  }
  // make key axis range scroll with the data (at a constant range size of 8):
  customPlot->xAxis->setRange(key+0.25, 8, Qt::AlignRight);
  customPlot->replot();
}


Window::~Window()
{

}

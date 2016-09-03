#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"

class Window : public QWidget
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = 0);
    ~Window();

private:
    QCustomPlot *customPlot;
};

#endif // WINDOW_H

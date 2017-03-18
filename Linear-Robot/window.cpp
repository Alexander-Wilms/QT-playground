#include "window.h"
#include <vector>
#include <QGridLayout>
#include <iostream>
#include <cmath>

#define RAD2DEG 180/M_PI

#define SAMPLES 200

double oldvalue = 0;
std::vector<double> x_values;
std::vector<double> y_values;

Window::Window(QWidget *parent) :
 QWidget(parent)
{
    setWindowTitle("My first QTCustomPlot - realtime");
    setMinimumSize(500,500);

    QGridLayout* grid = new QGridLayout(this);

    customPlot0 = new QCustomPlot(this);
    customPlot1 = new QCustomPlot(this);
    customPlot2 = new QCustomPlot(this);
    customPlot3 = new QCustomPlot(this);

    grid->addWidget(customPlot0,0,0);
    grid->addWidget(customPlot1,0,1);
    grid->addWidget(customPlot2,1,0);
    grid->addWidget(customPlot3,1,1);

    customPlot0->setSizePolicy(QSizePolicy ::Expanding , QSizePolicy ::Expanding);
    customPlot0->setMinimumHeight(250);
    customPlot0->setMinimumWidth(250);

    customPlot1->setSizePolicy(QSizePolicy ::Expanding , QSizePolicy ::Expanding);
    customPlot1->setMinimumHeight(250);
    customPlot1->setMinimumWidth(250);

    customPlot2->setSizePolicy(QSizePolicy ::Expanding , QSizePolicy ::Expanding);
    customPlot2->setMinimumHeight(250);
    customPlot2->setMinimumWidth(250);

    customPlot3->setSizePolicy(QSizePolicy ::Expanding , QSizePolicy ::Expanding);
    customPlot3->setMinimumHeight(250);
    customPlot3->setMinimumWidth(250);

    // create graph and assign data to it:
    customPlot0->addGraph();
    customPlot1->addGraph();
    customPlot2->addGraph();
    customPlot3->addGraph();

    // give the axes some labels:
    customPlot0->xAxis->setLabel("x");
    customPlot0->yAxis->setLabel("y");

    customPlot1->xAxis->setLabel("q1");
    customPlot1->yAxis->setLabel("q2");

    customPlot2->xAxis->setLabel("sample");
    customPlot2->yAxis->setLabel("q1");

    customPlot3->xAxis->setLabel("sample");
    customPlot3->yAxis->setLabel("q2");

    // set axes ranges, so we see all data:
    customPlot0->xAxis->setRange(0, 1);
    customPlot0->yAxis->setRange(0, 2);

    // interpolate line

    double x_start = 120;
    double x_end = -120;
    double x_delta = x_end - x_start;
    double x_step = x_delta / SAMPLES;
    std::cout << "x_step: " << x_step << std::endl;

    double y_start = 260;
    double y_end = 200;
    double y_delta = y_end - y_start;
    double y_step = y_delta / SAMPLES;

    for(int i = 0; i < SAMPLES; i++) {
        x_values.push_back(x_start+i*x_step);
        std::cout << "x: " << x_start+i*x_step << std::endl;
        y_values.push_back(y_start+i*y_step);
        std::cout << "y: " << y_start+i*y_step << std::endl;
    }

    // connect timer's timeout signal with update() slot
    connect(&dataTimer, SIGNAL(timeout()), this, SLOT(update()));

    // start timer with 10 ms interval
    dataTimer.start(10);
}

void Window::update(void)
{
    static int i = 0;

    float x = x_values.at(i);
    float y = y_values.at(i);

    customPlot0->graph(0)->addData(x,y);
    customPlot0->graph(0)->rescaleKeyAxis();
    customPlot0->graph(0)->rescaleValueAxis();
    customPlot0->replot();

    std::vector<double> joint_values = inverse_kinematics(x,y,175,125);
    customPlot1->graph(0)->addData(joint_values.at(0)*RAD2DEG,joint_values.at(1)*RAD2DEG);
    customPlot1->graph(0)->rescaleKeyAxis();
    customPlot1->graph(0)->rescaleValueAxis();
    customPlot1->replot();

    customPlot2->graph(0)->addData(i,joint_values.at(0)*RAD2DEG);
    customPlot2->graph(0)->rescaleKeyAxis();
    customPlot2->graph(0)->rescaleValueAxis();
    customPlot2->replot();

    customPlot3->graph(0)->addData(i,joint_values.at(1)*RAD2DEG);
    customPlot3->graph(0)->rescaleKeyAxis();
    customPlot3->graph(0)->rescaleValueAxis();
    customPlot3->replot();

    i++;

    if(i == SAMPLES)
        dataTimer.stop();
}

std::vector<double> Window::inverse_kinematics(double x, double y, double l1, double l2) {
    std::vector<double> joint_values;

    double a = l2;
    double b = sqrt(pow(x,2)+pow(y,2));
    double c = l1;

    double q1 = atan2(y,x)-acos((pow(a,2)-pow(b,2)-pow(c,2))/(-2*b*c));
    double q2 = M_PI - M_PI/2 - ((M_PI-M_PI/2-atan2(y,x))-acos((pow(c,2)-pow(a,2)-pow(b,2))/(-2*a*b)))-q1;

    joint_values.push_back(q1);
    joint_values.push_back(q2);

    return joint_values;
}

Window::~Window()
{

}

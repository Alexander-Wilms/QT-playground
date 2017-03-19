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
    setWindowTitle("Linear robot demo");
    setMinimumSize(500,500);

    QGridLayout* grid = new QGridLayout(this);

    cartesian_plot = new QCustomPlot(this);
    cartesian_curve = new QCPCurve(cartesian_plot->xAxis, cartesian_plot->yAxis);

    link_1 = new QCPItemLine(cartesian_plot);
    cartesian_plot->addItem(link_1);
    link_1->setPen(QPen(Qt::red));

    link_2 = new QCPItemLine(cartesian_plot);
    cartesian_plot->addItem(link_2);
    link_2->setPen(QPen(Qt::green));

    cartesian_plot->yAxis->setRange(0,260);
    cartesian_plot->xAxis->setRange(-120,120);

    config_space_plot = new QCustomPlot(this);
    curve_in_config_space = new QCPCurve(config_space_plot->xAxis, config_space_plot->yAxis);

    q1_graph = new QCustomPlot(this);
    q2_graph = new QCustomPlot(this);

    grid->addWidget(cartesian_plot,0,0);
    grid->addWidget(config_space_plot,0,1);
    grid->addWidget(q1_graph,1,0);
    grid->addWidget(q2_graph,1,1);

    cartesian_plot->setSizePolicy(QSizePolicy ::Expanding , QSizePolicy ::Expanding);
    cartesian_plot->setMinimumHeight(250);
    cartesian_plot->setMinimumWidth(250);

    config_space_plot->setSizePolicy(QSizePolicy ::Expanding , QSizePolicy ::Expanding);
    config_space_plot->setMinimumHeight(250);
    config_space_plot->setMinimumWidth(250);

    q1_graph->setSizePolicy(QSizePolicy ::Expanding , QSizePolicy ::Expanding);
    q1_graph->setMinimumHeight(250);
    q1_graph->setMinimumWidth(250);

    q2_graph->setSizePolicy(QSizePolicy ::Expanding , QSizePolicy ::Expanding);
    q2_graph->setMinimumHeight(250);
    q2_graph->setMinimumWidth(250);

    // create graph and assign data to it:
    //cartesian_curve->addGraph();
    //curve_in_config_space->addGraph();
    q1_graph->addGraph();
    q2_graph->addGraph();

    // give the axes some labels:
    cartesian_plot->xAxis->setLabel("x");
    cartesian_plot->yAxis->setLabel("y");

    config_space_plot->xAxis->setLabel("q1");
    config_space_plot->yAxis->setLabel("q2");

    q1_graph->xAxis->setLabel("sample");
    q1_graph->yAxis->setLabel("q1");

    q2_graph->xAxis->setLabel("sample");
    q2_graph->yAxis->setLabel("q2");

    config_space_plot->xAxis->setRange(0,90);
    config_space_plot->yAxis->setRange(0,90);

    q1_graph->yAxis->setRange(0,90);
    q1_graph->xAxis->setRange(0,200);

    q2_graph->yAxis->setRange(0,90);
    q2_graph->xAxis->setRange(0,200);

    // set axes ranges, so we see all data:
    cartesian_plot->xAxis->setRange(0, 1);
    cartesian_plot->yAxis->setRange(0, 2);

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

    QVector<double> t,x,y,q1,q2;
    t.append(i);
    x.append(x_values.at(i));
    y.append(y_values.at(i));
    std::vector<double> joint_values = inverse_kinematics(x.at(0),y.at(0),175,125);

    cartesian_curve->addData(t,x,y);
    link_1->end->setCoords(cos(joint_values.at(0))*175,sin(joint_values.at(0))*175);

    link_2->start->setCoords(cos(joint_values.at(0))*175,sin(joint_values.at(0))*175);

    link_2->end->setCoords(cos(joint_values.at(0))*175+cos(joint_values.at(0)+joint_values.at(1))*125,sin(joint_values.at(0))*175+sin(joint_values.at(0)+joint_values.at(1))*125);

    cartesian_curve->rescaleAxes();
    //if(cartesian_plot->yAxis->range().lower > 0)
    //cartesian_plot->yAxis->setRangeLower(0);
    cartesian_plot->yAxis->setRange(0,260);
    cartesian_plot->xAxis->setRange(-120,120);
    //cartesian_plot->yAxis->setRange(0,250);
    //cartesian_plot->xAxis->setRange(-120,120);
    cartesian_plot->replot();


    q1.append(joint_values.at(0)*RAD2DEG);
    q2.append(joint_values.at(1)*RAD2DEG);
    curve_in_config_space->addData(t,q1,q2);
    //curve_in_config_space->rescaleAxes();
    config_space_plot->replot();

    q1_graph->graph(0)->addData(i,joint_values.at(0)*RAD2DEG);
    //q1_graph->graph(0)->rescaleAxes();
    q1_graph->replot();

    q2_graph->graph(0)->addData(i,joint_values.at(1)*RAD2DEG);
    //q2_graph->graph(0)->rescaleAxes();
    q2_graph->replot();

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

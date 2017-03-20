#include "window.h"
#include "qcustomplot.h"
#include <QPushButton>

Window::Window(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("LTI systems realtime");
    setMinimumSize(500,500);

    grid = new QGridLayout(this);

    customPlot = new QCustomPlot(this);
    customPlot->setSizePolicy(QSizePolicy ::Expanding , QSizePolicy ::Expanding);
    customPlot->addGraph();
    customPlot->yAxis->setRange(-1,1);
    customPlot->xAxis->setRange(0,10);

    x.resize(101);
    y.resize(101);

    update_graph();

    grid->addWidget(customPlot,0,0);

    QVBoxLayout *vbox = new QVBoxLayout(this);

    grid->addLayout(vbox,0,1);

    QPushButton *increase_amplitude_button = new QPushButton();
    QPushButton *decrease_amplitude_button = new QPushButton();
    QPushButton *increase_frequency_button = new QPushButton();
    QPushButton *decrease_frequency_button = new QPushButton();
    QPushButton *increase_phase_button = new QPushButton();
    QPushButton *decrease_phase_button = new QPushButton();

    increase_amplitude_button->setText("increase amplitude");
    decrease_amplitude_button->setText("decrease amplitude");
    increase_frequency_button->setText("increase frequency");
    decrease_frequency_button->setText("decrease frequency");
    increase_phase_button->setText("increase phase");
    decrease_phase_button->setText("decrease phase");

    vbox->addWidget(increase_amplitude_button);
    vbox->addWidget(decrease_amplitude_button);
    vbox->addWidget(increase_frequency_button);
    vbox->addWidget(decrease_frequency_button);
    vbox->addWidget(increase_phase_button);
    vbox->addWidget(decrease_phase_button);

    connect(increase_amplitude_button, SIGNAL (clicked(bool)), this, SLOT (slot_increase_amplitude()));
    connect(decrease_amplitude_button, SIGNAL (clicked(bool)), this, SLOT (slot_decrease_amplitude()));
    connect(increase_frequency_button, SIGNAL (clicked(bool)), this, SLOT (slot_increase_frequency()));
    connect(decrease_frequency_button, SIGNAL (clicked(bool)), this, SLOT (slot_decrease_frequency()));
    connect(increase_phase_button, SIGNAL (clicked(bool)), this, SLOT (slot_increase_phase()));
    connect(decrease_phase_button, SIGNAL (clicked(bool)), this, SLOT (slot_decrease_phase()));
}

void Window::slot_increase_amplitude()
{
    amplitude *= 1.1;
    update_graph();
}

void Window::slot_decrease_amplitude()
{
    amplitude /= 1.1;
    update_graph();
}

void Window::slot_increase_frequency()
{
    frequency *= 1.1;
    update_graph();
}

void Window::slot_decrease_frequency()
{
    frequency /= 1.1;
    update_graph();
}

void Window::slot_increase_phase()
{
    phase += 0.1;
    update_graph();
}

void Window::slot_decrease_phase()
{
    phase -= 0.1;
    update_graph();
}

void Window::update_graph() {
    for(int i=0; i < 101; i++) {
        x[i]=10./101*i;
        y[i]=amplitude*sin(frequency*x[i]+phase);
    }

    customPlot->graph(0)->setData(x,y);

    customPlot->replot();
}

Window::~Window()
{

}

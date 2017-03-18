#include "mainwindow.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QWidget>
#include <QString>

Window::Window(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout* layout = new QVBoxLayout();
    this->setLayout(layout);

    QPushButton* btn = new QPushButton(this);
    btn->setText("Hello World");

    layout->addWidget(btn);

    lab = new QLabel(this);
    lab->setText("Hello World");
    layout->addWidget(lab);

    counter = 1;

    connect(btn, SIGNAL (clicked(bool)), this, SLOT (buttonClicked()));
}

void Window::buttonClicked()
{
    QString str;
    str = QString::number(counter);
    lab->setText(str);
    counter++;
}

#include "window.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    this->setFixedHeight(200);
    this->setFixedWidth(150);

    vlayout = new QVBoxLayout(this);

    QHBoxLayout *addline = new QHBoxLayout();



    edit = new QLineEdit();

    QPushButton *btn = new QPushButton();

    btn->setMaximumWidth(25);

    addline->addWidget(edit);

    addline->addWidget(btn);

    btn->setText("+");

    vlayout->addLayout(addline);

    vlayout->setAlignment(Qt::AlignTop);

    connect(btn,SIGNAL(clicked(bool)),this,SLOT(add_item()));

    QVector<QHBoxLayout*> items;
}

void Widget::add_item() {
    layouts.push_back(new QHBoxLayout);
    checkboxes.push_back(new QCheckBox);
    labels.push_back(new QLabel);
    layouts.back()->setAlignment(Qt::AlignLeft);
    layouts.back()->addWidget(checkboxes.back());
    layouts.back()->addWidget(labels.back());
    labels.back()->setText(edit->text());
    edit->clear();
    vlayout->addLayout(layouts.back());
}

Widget::~Widget()
{

}

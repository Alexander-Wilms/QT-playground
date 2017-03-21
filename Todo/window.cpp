#include "window.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <iostream>

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

    connect(edit,SIGNAL(returnPressed()),this,SLOT(add_item()));

    signalMapper = new QSignalMapper(this);

    connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(remove_item(int)));

    numberofitems = 0;
}

void Widget::add_item() {
    if(edit->text() != "") {
        numberofitems++;
        layouts.push_back(new QHBoxLayout);
        checkboxes.push_back(new QCheckBox());
        labels.push_back(new QLabel);
        layouts.back()->setAlignment(Qt::AlignLeft);
        layouts.back()->addWidget(checkboxes.back());
        layouts.back()->addWidget(labels.back());
        labels.back()->setText(edit->text());
        edit->clear();
        vlayout->addLayout(layouts.back());

        connect(checkboxes.back(),SIGNAL(clicked()),signalMapper,SLOT(map()));
        signalMapper->setMapping(checkboxes.back(),numberofitems);
    }
}

void Widget::remove_item(int i){
    std::cout << "trying to remove item " << i << std::endl;
    vlayout->removeItem(layouts.at(i-1));
    delete labels.at(i-1);
    delete checkboxes.at(i-1);
    delete layouts.at(i-1);
}

Widget::~Widget()
{

}

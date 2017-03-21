#include "window.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <iostream>
#include <QFile>
#include <QTextStream>

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

    connect(btn,SIGNAL(clicked(bool)),this,SLOT(add_item_frontend()));

    connect(edit,SIGNAL(returnPressed()),this,SLOT(add_item_frontend()));

    signalMapper = new QSignalMapper(this);

    connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(remove_item(int)));

    numberofitems = 0;

    file = new QFile("todo.txt");

    if(file->open(QIODevice::ReadWrite)) {
        QTextStream in(file);
        while(!in.atEnd()) {
            add_item(in.readLine());
            std::cout << "reading 1 line" << std::endl;
        }
        file->close();
    }
}

void Widget::add_item(QString text) {
    if(text != "") {
        numberofitems++;
        layouts.push_back(new QHBoxLayout);
        checkboxes.push_back(new QCheckBox());
        labels.push_back(new QLabel);
        layouts.back()->setAlignment(Qt::AlignLeft);
        layouts.back()->addWidget(checkboxes.back());
        layouts.back()->addWidget(labels.back());
        labels.back()->setText(text);
        edit->clear();
        vlayout->addLayout(layouts.back());

        connect(checkboxes.back(),SIGNAL(clicked()),signalMapper,SLOT(map()));
        signalMapper->setMapping(checkboxes.back(),numberofitems);
    }
}

void Widget::add_item_frontend() {
    add_item(edit->text());
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
    std::cout << "closing" << std::endl;
    if(file->open(QIODevice::ReadWrite | QIODevice::Truncate)) {
        QTextStream out(file);
        QVectorIterator<QLabel*> iter(labels);
        while(iter.hasNext()) {
            out << iter.next()->text() << "\r\n";
        }
        file->close();
    }
}

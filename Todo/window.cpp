#include "window.h"
#include <QCheckBox>
#include <QFile>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QScrollArea>
#include <QTextStream>
#include <QVBoxLayout>
#include <iostream>

Widget::Widget(QWidget *parent) : QWidget(parent) {
    this->setMinimumHeight(200);

    this->setMinimumWidth(150);

    v_top_layout = new QVBoxLayout(this);

    v_top_layout->setAlignment(Qt::AlignTop);

    QHBoxLayout *addline = new QHBoxLayout();

    edit = new QLineEdit();

    QPushButton *btn = new QPushButton();

    btn->setMaximumWidth(25);

    addline->addWidget(edit);

    addline->addWidget(btn);

    btn->setText("+");

    v_top_layout->addLayout(addline);

    v_item_layout = new QVBoxLayout();

    QScrollArea *area = new QScrollArea();

    QWidget *scrollAreaContent = new QWidget;

    area->setAlignment(Qt::AlignTop);

    // scrollAreaContent->setSizePolicy(QSizePolicy::Policy::ExpandFlag);

    scrollAreaContent->setLayout(v_item_layout);

    // area->setAlignment(Qt::AlignTop);

    v_item_layout->setAlignment(Qt::AlignTop);

    area->setWidgetResizable(true);

    area->setWidget(scrollAreaContent);

    area->setFrameShape(QFrame::NoFrame);

    v_top_layout->addWidget(area);

    connect(btn, SIGNAL(clicked(bool)), this, SLOT(add_item_frontend()));

    connect(edit, SIGNAL(returnPressed()), this, SLOT(add_item_frontend()));

    signalMapper = new QSignalMapper(this);

    connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(remove_item(int)));

    id = 0;

    file = new QFile("todo.txt");

    if (file->open(QIODevice::ReadWrite)) {
        QTextStream in(file);
        while (!in.atEnd()) {
            add_item(in.readLine());
            std::cout << "reading 1 line" << std::endl;
        }
        file->close();
    }
}

void Widget::add_item(QString text) {
    if (text != "") {
        std::cout << "adding item with ID " << id << std::endl;
        ids.push_back(id);
        layouts.push_back(new QHBoxLayout);
        checkboxes.push_back(new QCheckBox());
        labels.push_back(new QLabel);
        layouts.back()->setAlignment(Qt::AlignLeft);
        layouts.back()->addWidget(checkboxes.back());
        layouts.back()->addWidget(labels.back());
        labels.back()->setText(text);
        edit->clear();
        v_item_layout->addLayout(layouts.back());

        connect(checkboxes.back(), SIGNAL(clicked()), signalMapper,
                SLOT(map()));
        signalMapper->setMapping(checkboxes.back(), id);

        id++;
    }
}

void Widget::add_item_frontend() { add_item(edit->text()); }

void Widget::remove_item(int i) {
    std::cout << "trying to remove item with ID " << i << std::endl;
    QMutableVectorIterator<int> iter_ids(ids);
    QMutableVectorIterator<QLabel *> iter_labels(labels);
    QMutableVectorIterator<QHBoxLayout *> iter_layouts(layouts);
    QMutableVectorIterator<QCheckBox *> iter_checkboxes(checkboxes);

    bool found = false;

    while (!found && iter_ids.hasNext()) {
        if (iter_ids.next() == i) {
            std::cout << i << std::endl;
            found = true;

            delete iter_labels.next();
            delete iter_checkboxes.next();
            delete iter_layouts.next();

            iter_ids.remove();
            iter_labels.remove();
            iter_checkboxes.remove();
            iter_layouts.remove();
        } else {
            // iter_ids has already advanced, if the other ones don't advance there will be a discrepancy
            iter_labels.next();
            iter_checkboxes.next();
            iter_layouts.next();
        }
    }
}

Widget::~Widget() {
    std::cout << "closing" << std::endl;
    if (file->open(QIODevice::ReadWrite | QIODevice::Truncate)) {
        QTextStream out(file);
        QVectorIterator<QLabel *> iter(labels);
        std::cout << "before while" << std::endl;
        while (iter.hasNext()) {
            std::cout << "in while" << std::endl;
            out << iter.next()->text() << "\r\n";
        }
        std::cout << "after while" << std::endl;
        file->close();
    }
}

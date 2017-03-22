// https://wiki.qt.io/Basic_Qt_Programming_Tutorial

#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;

    w.setName("Slim Shady");

    w.show();

    return a.exec();
}

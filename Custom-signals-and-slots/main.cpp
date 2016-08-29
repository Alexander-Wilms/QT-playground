#include <QApplication>
#include <QProgressBar>
#include<QPushButton>
#include <QSlider>
#include "window.h"

int main(int argc, char **argv)
{
    QApplication app (argc, argv);

    Window parent;
    parent.show();

    return app.exec();
}

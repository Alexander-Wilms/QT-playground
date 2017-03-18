#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QLabel>

class Window : public QWidget
{
    Q_OBJECT

public:
    Window(QWidget *parent = 0);
signals:
    void counterReached();
private slots:
    void buttonClicked();
private:
    int counter;
    QLabel* lab;
};

#endif // MAINWINDOW_H

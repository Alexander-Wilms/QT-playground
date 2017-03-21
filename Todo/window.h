#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QCheckBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QVector>
#include <array>
#include <QSignalMapper>
#include <QFile>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

private:
    QVBoxLayout *vlayout;
    QLineEdit *edit;
    QVector<QHBoxLayout*> layouts;
    QVector<QCheckBox*> checkboxes;
    QVector<QLabel*> labels;
    QSignalMapper * signalMapper;
    int numberofitems;
    QFile *file;

private slots:
    void add_item(QString text);
    void add_item_frontend();
    void remove_item(int i);
};

#endif // WINDOW_H

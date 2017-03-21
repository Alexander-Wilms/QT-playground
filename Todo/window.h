#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QCheckBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QVector>
#include <array>


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

private slots:
    void add_item();
};

#endif // WINDOW_H

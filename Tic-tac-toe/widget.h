#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QSignalMapper>
#include <vector>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

private:
    QVector<QPushButton*> buttons;
    QVector<int> ids;
    QVector<bool> completed_cells;
    QSignalMapper *signalMapper;
    std::vector<std::vector<char>> game_state;
    bool check_if_won();
    int round;

private slots:
    void cell_clicked(int);
};

#endif // WIDGET_H

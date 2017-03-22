#ifndef WINDOW_H
#define WINDOW_H

#include <QCheckBox>
#include <QFile>
#include <QLabel>
#include <QLineEdit>
#include <QSignalMapper>
#include <QVBoxLayout>
#include <QVector>
#include <QWidget>
#include <array>

class Widget : public QWidget {
    Q_OBJECT

  public:
    Widget(QWidget *parent = 0);
    ~Widget();

  private:
    QVBoxLayout *v_top_layout;
    QVBoxLayout *v_item_layout;
    QLineEdit *edit;
    QVector<QHBoxLayout *> layouts;
    QVector<int> ids;
    QVector<QCheckBox *> checkboxes;
    QVector<QLabel *> labels;
    QSignalMapper *signalMapper;
    int id;
    QFile *file;

  private slots:
    void add_item(QString text);
    void add_item_frontend();
    void remove_item(int i);
};

#endif // WINDOW_H

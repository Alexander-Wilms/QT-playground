#include "widget.h"
#include <QGridLayout>
#include <QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    signalMapper = new QSignalMapper(this);

    connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(cell_clicked(int)));

    QGridLayout *grid = new QGridLayout(this);

    for(int i = 0; i < 9; i++) {
        buttons.push_back(new QPushButton());
        buttons.back()->setMaximumWidth(50);
        grid->addWidget(buttons.back(),i%3,i/3);
        connect(buttons.back(), SIGNAL(clicked()), signalMapper,SLOT(map()));
        signalMapper->setMapping(buttons.back(), i);
    }

    game_state.resize(3);
    game_state.at(0).resize(3);
    game_state.at(1).resize(3);
    game_state.at(2).resize(3);

    for(int i = 0; i < 9; i++)
    {
        game_state.at(i%3).at(i/3) = 0x30+i;
    }

    round = 0;
}

void Widget::cell_clicked(int cell)
{
    buttons.at(cell)->setEnabled(false);

    if(round%2 == 0)
    {
        buttons.at(cell)->setText("X");
        game_state.at(cell%3).at(cell/3) = 'x';
    } else
    {
        buttons.at(cell)->setText("O");
        game_state.at(cell%3).at(cell/3) = 'o';
    }

    if(check_if_won())
    {
        QVectorIterator<QPushButton*> iter(buttons);
        while(iter.hasNext())
        {
            iter.next()->setEnabled(false);
        }

        QMessageBox msg;
        msg.setText("You won!");
        msg.exec();
    }

    round++;
}

bool Widget::check_if_won()
{
    return(\
        (game_state.at(0).at(0) == game_state.at(0).at(1) && game_state.at(0).at(1) == game_state.at(0).at(2)) || // |..
        (game_state.at(1).at(0) == game_state.at(1).at(1) && game_state.at(1).at(1) == game_state.at(1).at(2)) || // .|.
        (game_state.at(2).at(0) == game_state.at(2).at(1) && game_state.at(2).at(1) == game_state.at(2).at(2)) || // ..|
        \
        (game_state.at(0).at(0) == game_state.at(1).at(0) && game_state.at(1).at(0) == game_state.at(2).at(0)) || // /..
        (game_state.at(0).at(1) == game_state.at(1).at(1) && game_state.at(1).at(1) == game_state.at(2).at(1)) || // ./.
        (game_state.at(0).at(2) == game_state.at(1).at(2) && game_state.at(1).at(2) == game_state.at(2).at(2)) || // ../
        \
        (game_state.at(0).at(0) == game_state.at(1).at(1) && game_state.at(1).at(1) == game_state.at(2).at(2)) || // diag
        (game_state.at(0).at(2) == game_state.at(1).at(1) && game_state.at(1).at(1) == game_state.at(2).at(0)));  // diag

}

Widget::~Widget()
{

}

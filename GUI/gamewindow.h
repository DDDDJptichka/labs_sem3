#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>

#include "Board.hpp"
#include "Bot.hpp"

class GameWindow : public QWidget{

    private:

        Board board;
        Bot bot;
        size_t cell_size = 40;
        bool game_over = false;
        bool bot_turn = false;

        void make_bot_move();

    protected:

        void paintEvent(QPaintEvent* event) override;
        void mousePressEvent(QMouseEvent* event) override;

    public:

        explicit GameWindow(QWidget *parent = nullptr);

        ~GameWindow() override;

};

#endif

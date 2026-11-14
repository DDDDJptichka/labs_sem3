#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QPoint>

#include "Board.hpp"
#include "Bot.hpp"

class GameWindow : public QWidget{

    private:

        Board board;
        Bot bot;
        int cell_size = 40;
        bool game_over = false;
        bool bot_turn = false;

        int offset_x = 0;
        int offset_y = 0;
        bool dragging = false;
        QPoint last_mouse_pos;

        void make_bot_move();

    protected:

        void paintEvent(QPaintEvent* event) override;
        void mousePressEvent(QMouseEvent* event) override;
        void mouseMoveEvent(QMouseEvent* event) override;
        void mouseReleaseEvent(QMouseEvent* event) override;

    public:

        explicit GameWindow(QWidget *parent = nullptr);

        ~GameWindow() override;

};

#endif

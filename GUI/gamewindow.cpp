#include "gamewindow.h"

#include <QPainter>
#include <QMouseEvent>
#include <QTimer>

#include <cmath>

size_t position_hash(Position pos){

    return pos.get_x() * 337 + pos.get_y() * 228;

}

GameWindow::GameWindow(QWidget *parent) : QWidget(parent), board(position_hash, 222), bot(Cell::O){

    setWindowTitle("Your turn");
    resize(900, 700);

}

GameWindow::~GameWindow() = default;

void GameWindow::paintEvent(QPaintEvent* event){

    QPainter painter(this);
    painter.fillRect(rect(), QColor(30, 30, 40));

    int origin_x = width() / 2 - cell_size / 2 + offset_x;
    int origin_y = height() / 2 - cell_size / 2 + offset_y;

    painter.setPen(QPen(QColor(80, 80, 95), 1));

    int start_x = ((origin_x % cell_size) + cell_size) % cell_size;
    int start_y = ((origin_y % cell_size) + cell_size) % cell_size;

    for (int x = start_x; x <= width(); x += cell_size){

        painter.drawLine(x, 0, x, height());

    }

    for (int y = start_y; y <= height(); y += cell_size){

        painter.drawLine(0, y, width(), y);

    }

    ListSequence<Position> positions = board.get_occupied_pos();
    size_t count = positions.get_length();

    for (size_t i = 0; i < count; ++i){

        Position pos = positions[i];
        Cell cell = board.get_cell(pos);

        int x = origin_x + pos.get_x() * cell_size;
        int y = origin_y + pos.get_y() * cell_size;

        QRect cell_rect(x, y, cell_size, cell_size);

        if (rect().intersects(cell_rect) == false){

            continue;

        }

        if (cell == Cell::X){

            painter.setPen(QPen(QColor(100, 180, 255), 3));
            painter.drawLine(x + 8, y + 8, x + cell_size - 8, y + cell_size - 8);
            painter.drawLine(x + cell_size - 8, y + 8, x + 8, y + cell_size - 8);

        }
        else if (cell == Cell::O){

            painter.setPen(QPen(QColor(255, 170, 100), 3));
            painter.drawEllipse(x + 8, y + 8, cell_size - 16, cell_size - 16);

        }

    }

}

void GameWindow::mousePressEvent(QMouseEvent* event){

    if (event->button() == Qt::RightButton){

        dragging = true;
        last_mouse_pos = event->pos();

        return;

    }

    if (event->button() != Qt::LeftButton){

        return;

    }

    if (game_over || bot_turn){

        return;

    }

    int origin_x = width() / 2 - cell_size / 2 + offset_x;
    int origin_y = height() / 2 - cell_size / 2 + offset_y;
    int x = std::floor((event->position().x() - origin_x) / cell_size);
    int y = std::floor((event->position().y() - origin_y) / cell_size);

    Position pos(x, y);

    if (board.is_free(pos) == false){

        return;

    }

    board.make_move(pos, Cell::X);
    update();

    if (board.check_win(pos, Cell::X)){

        game_over = true;
        setWindowTitle("Five in Row - You win!");

        return;

    }

    bot_turn = true;
    setWindowTitle("Five in Row - Bot is thinking...");
    QTimer::singleShot(30, this, [this](){make_bot_move();});

}

void GameWindow::make_bot_move(){

    if (game_over){

        return;

    }

    Position pos = bot.find_best_move(board);
    board.make_move(pos, Cell::O);
    update();

    if (board.check_win(pos, Cell::O)){

        game_over = true;
        setWindowTitle("Five in Row - Bot wins!");

        return;

    }

    bot_turn = false;
    setWindowTitle("Five in Row - Your turn");

}

void GameWindow::mouseMoveEvent(QMouseEvent* event){

    if (dragging == false){

        return;

    }

    QPoint delta = event->pos() - last_mouse_pos;

    offset_x += delta.x();
    offset_y += delta.y();
    last_mouse_pos = event->pos();

    update();

}

void GameWindow::mouseReleaseEvent(QMouseEvent* event){

    if (event->button() == Qt::RightButton){

        dragging = false;

    }

}
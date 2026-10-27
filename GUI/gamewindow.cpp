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

void GameWindow::paintEvent(QPaintEvent* event){}

void GameWindow::mousePressEvent(QMouseEvent* event){}
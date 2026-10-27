#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>

class GameWindow : public QWidget
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow() override;
};
#endif // GAMEWINDOW_H

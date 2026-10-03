#pragma once

class Position{

    private:

        int x;
        int y;

    public:

        Position(int x, int y) : x(x), y(y){}

        int get_x() const{

            return x;

        }

        int get_y() const{

            return y;

        }

        bool operator==(const Position& another) const{

            return (x == another.x) && (y == another.y);

        }

};
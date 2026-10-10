#pragma once

#include "HashTable.hpp"
#include "Position.hpp"
#include "Cell.hpp"

class Board{

    private:

        HashTable<Position, Cell> board;

    public:

        Board(size_t (*hash_function)(Position), size_t capacity) : board(hash_function, capacity){}

        size_t get_capacity() const{

            return board.get_capacity();

        }

        bool is_free(Position pos) const{

            return !(board.contains_key(pos));

        }

        Cell get_cell(Position pos) const{

            if (board.contains_key(pos) == 1){

                return board.get(pos);

            }

            return Cell::Empty;

        }

        void make_move(Position pos, Cell elem){

            board.add(pos, elem);

        }

        void remove_move(Position pos){

            board.remove(pos);

        }

};
#pragma once

#include "HashTable.hpp"
#include "Position.hpp"
#include "Cell.hpp"

class Board{

    private:

        HashTable<Position, Cell> board;
        HashTable<Position, size_t> possible_moves;

    public:

        Board(size_t (*hash_function)(Position), size_t capacity) : board(hash_function, capacity), possible_moves(hash_function, capacity){}

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

            if (possible_moves.contains_key(pos)){

                possible_moves.remove(pos);

            }

            int dirs[8][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}, {1, 1}, {-1, 1}, {1, -1}, {-1, -1}};

            for(auto &dir : dirs){

                Position possib_pos = pos + Position(dir[0], dir[1]);

                if (possible_moves.contains_key(possib_pos)){

                    possible_moves[possib_pos]++;

                }
                else{

                    if (board.contains_key(possib_pos) == 0){

                        possible_moves.add(possib_pos, 1);

                    }

                }

            }

        }

        void remove_move(Position pos){

            board.remove(pos);

        }

        bool check_win(Position pos, Cell cell){

            int dirs[3][2][2] = {{{-1, 0}, {1, 0}}, {{0, -1}, {0, 1}}, {{-1, -1}, {1, 1}}};

            for (auto &dir : dirs){

                size_t count = 1;

                for (auto &d : dir){

                    Position curr_pos = pos;
                    
                    while (cell == get_cell(curr_pos + Position(d[0], d[1]))){

                        curr_pos = curr_pos + Position(d[0], d[1]);
                        ++count;

                        if (count >= 5){

                            return true;

                        }

                    }

                }

            }

            return false;

        }

        bool is_move_possible(Position pos){

            return possible_moves.contains_key(pos);

        }

};
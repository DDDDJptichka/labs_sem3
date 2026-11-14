#pragma once

#include "HashTable.hpp"
#include "Position.hpp"
#include "Cell.hpp"

class Board{

    private:

        HashTable<Position, Cell> board;
        HashTable<Position, size_t> possible_moves;

    public:

        Board(size_t (*hash_function)(Position), size_t bucket_count) : board(hash_function, bucket_count), possible_moves(hash_function, bucket_count){}

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

            size_t neighb_count = 0;
            int dirs[8][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}, {1, 1}, {-1, 1}, {1, -1}, {-1, -1}};

            for (auto &dir : dirs){

                Position del_pos = pos + Position(dir[0], dir[1]);

                if (board.contains_key(del_pos)){

                    ++neighb_count;

                }

                if (possible_moves.contains_key(del_pos)){

                    if (possible_moves.get(del_pos) == 1){

                        possible_moves.remove(del_pos);

                    }
                    else{

                        --possible_moves[del_pos];

                    }

                }

            }

            if (neighb_count > 0){

                possible_moves.add(pos, neighb_count);

            }

        }

        bool check_win(Position pos, Cell cell){

            int dirs[4][2][2] = {{{-1, 0}, {1, 0}}, {{0, -1}, {0, 1}}, {{-1, -1}, {1, 1}}, {{-1, 1}, {1, -1}}};

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

        bool is_move_possible(Position pos) const{

            if ((possible_moves.get_count() == 0) && (board.get_count() == 0)){

                return (Position(0, 0) == pos);

            }

            return possible_moves.contains_key(pos);

        }

        size_t neighbour_count(Position pos) const{

            if ((board.get_count() == 0) && (pos == Position(0, 0))){

                return 0;

            }

            return possible_moves.get(pos);

        }

        ListSequence<Position> get_possible_moves() const{

            if (board.get_count() == 0){

                ListSequence<Position> moves;
                moves.append(Position(0, 0));

                return moves;

            }

            return possible_moves.get_keys();

        }

        size_t get_possible_moves_count() const{

            if ((possible_moves.get_count() == 0) && (board.get_count() == 0)){

                return 1;

            }

            return possible_moves.get_count();

        }

        ListSequence<Position> get_occupied_pos() const{

            return board.get_keys();

        }

};
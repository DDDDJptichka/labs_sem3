#pragma once

#include "Board.hpp"
#include "HashTable.hpp"
#include "Position.hpp"
#include "Cell.hpp"

class Bot{

    private:

        Cell bot_cell;

    public:

        Bot(Cell cell) : bot_cell(cell){}

        int pattern_score(size_t len, size_t open_ends){

            int score = 0;

            if ((len == 1) && (open_ends == 1)){

                score += 1;

            }
            else if ((len == 1) && (open_ends == 2)){

                score += 2;

            }
            else if ((len == 2) && (open_ends == 1)){

                score += 10;

            }
            else if ((len == 2) && (open_ends == 2)){

                score += 100;

            }
            else if ((len == 3) && (open_ends == 1)){

                score += 1000;

            }
            else if ((len == 3) && (open_ends == 2)){

                score += 10000;

            }
            else if ((len == 4) && (open_ends == 1)){

                score += 100000;

            }
            else if ((len == 4) && (open_ends == 2)){

                score += 1000000;

            }
            else if (len >= 5){

                score += 10000000;

            }

            return score;

        }

        int evaluate_pattern(Board& board, Position pos, Cell cell){

            if ((cell == Cell::Empty) || (board.is_free(pos) == 0)){

                return 0;
                
            }

            Position dirs[4] = {Position(1, 0), Position(0, 1), Position(1, 1), Position(1, -1)};
            int sum = 0;

            for (auto &dir : dirs){
                
                int start = -4;
                int end = -5;

                for (int i = -4; i < 5; ++i){

                    Position curr = pos + dir * i;

                    if ((cell == board.get_cell(curr)) || (i == 0)){

                        end = i;

                    }
                    else{

                        if (i > 0){

                            break;

                        }

                        start = i + 1;
                        end = i;

                    }

                }

                size_t len = end - start + 1;
                size_t open_ends = 0;

                if (board.get_cell(pos + dir * (start - 1)) == Cell::Empty){

                    ++open_ends;

                }

                if (board.get_cell(pos + dir * (end + 1)) == Cell::Empty){

                    ++open_ends;

                }

                sum += pattern_score(len, open_ends);

            }

            return sum;

        }

        int evaluate_move(Board& board, Position pos, Cell cell){

            Cell enemy;

            if (cell == Cell::X){

                enemy = Cell::O;

            }
            else{

                enemy = Cell::X;

            }

            return evaluate_pattern(board, pos, cell) + evaluate_pattern(board, pos, enemy);

        }

};
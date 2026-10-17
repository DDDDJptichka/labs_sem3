#pragma once

#include "Board.hpp"
#include "HashTable.hpp"
#include "Position.hpp"
#include "Cell.hpp"

#define INF 1000000000000000
#define WIN 1000000000000001
#define LOSE -1000000000000001

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

            Cell enemy = !cell;

            return evaluate_pattern(board, pos, cell) + evaluate_pattern(board, pos, enemy);

        }

        long long int evaluate(Board& board){

            Cell enemy = !bot_cell;
            
            ListSequence<Position> poss_moves = board.get_possible_moves();
            size_t count = poss_moves.get_length();
            long long int res = 0; 

            for (size_t i = 0; i < count; ++i){

                Position pos = poss_moves[i];
                res = res + evaluate_pattern(board, pos, bot_cell) - evaluate_pattern(board, pos, enemy);

            }

            return res;

        }

        long long int minimax(Board& board, int depth, long long int a, long long int b, bool maxi){

            if (depth == 0){

                return evaluate(board);

            }

            Cell curr = maxi ? bot_cell : !bot_cell;
            ListSequence<Position> poss_moves = board.get_possible_moves();
            size_t count = poss_moves.get_length();
            long long int best = maxi ? -INF : INF;

            for (size_t i = 0; i < count; ++i){

                Position pos = poss_moves[i];
                board.make_move(pos, curr);
                long long int check_sum = 0;

                if (board.check_win(pos, curr)){

                    check_sum = maxi ? WIN : LOSE;

                }
                else{

                    check_sum = minimax(board, depth - 1, a, b, !maxi);

                }

                board.remove_move(pos);

                if (maxi){

                    best = std::max(best, check_sum);
                    a = std::max(a, best);

                }
                else{

                    best = std::min(best, check_sum);
                    b = std::min(b, best);

                }

                if (b <= a){

                    break;

                }

            }

            return best;

        }

        Position find_best_move(Board& board){

            ListSequence<Position> poss_moves = board.get_possible_moves();
            size_t len = poss_moves.get_length();

            Position best_pos;
            long long int a = -INF;
            long long int best = -INF;

            size_t depth = 4;

            for (size_t i = 0; i < len; ++i){

                Position curr = poss_moves[i];
                board.make_move(curr, bot_cell);
                long long int check_sum = 0;

                if (board.check_win(curr, bot_cell)){

                    check_sum = INF;

                }
                else{

                    check_sum = minimax(board, depth - 1, a, INF, false);

                }

                board.remove_move(curr);

                if (check_sum > best){

                    best_pos = curr;
                    best = check_sum;

                }

                a = std::max(a, best);

            }

            return best_pos;

        }

};
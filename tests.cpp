#include <gtest/gtest.h>

#include "includes/LinkedList.hpp"
#include "includes/ListSequence.hpp"
#include "includes/HashTable.hpp"
#include "includes/Position.hpp"
#include "includes/Cell.hpp"
#include "includes/Board.hpp"
#include "includes/Bot.hpp"

#define INF 1000000000000000
#define WIN 1000000000000001
#define LOSE -1000000000000001

TEST(LinkedList, CreateEmpty){

    LinkedList<int> list;

    EXPECT_EQ(list.get_length(), 0);

}

TEST(LinkedList, Append){

    LinkedList<int> list;

    list.append(10);
    list.append(20);
    list.append(30);

    EXPECT_EQ(list.get_length(), 3);
    EXPECT_EQ(list.get_first(), 10);
    EXPECT_EQ(list.get_last(), 30);

}

TEST(LinkedList, Prepend){

    LinkedList<int> list;

    list.prepend(10);
    list.prepend(20);
    list.prepend(30);

    EXPECT_EQ(list.get_length(), 3);
    EXPECT_EQ(list.get_first(), 30);
    EXPECT_EQ(list.get_last(), 10);

}

TEST(LinkedList, Get){

    LinkedList<int> list;

    list.append(10);
    list.append(20);
    list.append(30);

    EXPECT_EQ(list.get(0), 10);
    EXPECT_EQ(list.get(1), 20);
    EXPECT_EQ(list.get(2), 30);

}

TEST(LinkedList, Set){

    LinkedList<int> list;

    list.append(10);
    list.append(20);
    list.append(30);

    list.set(1, 100);

    EXPECT_EQ(list.get(0), 10);
    EXPECT_EQ(list.get(1), 100);
    EXPECT_EQ(list.get(2), 30);

}

TEST(LinkedList, InsertAtMiddle){

    LinkedList<int> list;

    list.append(10);
    list.append(30);

    list.insert_at(20, 1);

    EXPECT_EQ(list.get_length(), 3);
    EXPECT_EQ(list.get(0), 10);
    EXPECT_EQ(list.get(1), 20);
    EXPECT_EQ(list.get(2), 30);

}

TEST(LinkedList, InsertAtBeginning){

    LinkedList<int> list;

    list.append(20);
    list.append(30);

    list.insert_at(10, 0);

    EXPECT_EQ(list.get_first(), 10);
    EXPECT_EQ(list.get_length(), 3);

}

TEST(LinkedList, InsertAtEnd){

    LinkedList<int> list;

    list.append(10);
    list.append(20);

    list.insert_at(30, 2);

    EXPECT_EQ(list.get_last(), 30);
    EXPECT_EQ(list.get_length(), 3);

}

TEST(LinkedList, RemoveAtMiddle){

    LinkedList<int> list;

    list.append(10);
    list.append(20);
    list.append(30);

    list.remove_at(1);

    EXPECT_EQ(list.get_length(), 2);
    EXPECT_EQ(list.get(0), 10);
    EXPECT_EQ(list.get(1), 30);

}

TEST(LinkedList, RemoveFirst){

    LinkedList<int> list;

    list.append(10);
    list.append(20);
    list.append(30);

    list.remove_at(0);

    EXPECT_EQ(list.get_length(), 2);
    EXPECT_EQ(list.get_first(), 20);

}

TEST(LinkedList, RemoveLast){

    LinkedList<int> list;

    list.append(10);
    list.append(20);
    list.append(30);

    list.remove_at(2);

    EXPECT_EQ(list.get_length(), 2);
    EXPECT_EQ(list.get_last(), 20);

}

TEST(LinkedList, RemoveOnlyElement){

    LinkedList<int> list;

    list.append(10);

    list.remove_at(0);

    EXPECT_EQ(list.get_length(), 0);

}

TEST(LinkedList, OperatorIndex){

    LinkedList<int> list;

    list.append(10);
    list.append(20);

    EXPECT_EQ(list[0], 10);
    EXPECT_EQ(list[1], 20);

}

TEST(LinkedList, CopyConstructor){

    LinkedList<int> list;

    list.append(10);
    list.append(20);
    list.append(30);

    LinkedList<int> copy(list);

    EXPECT_EQ(copy.get_length(), 3);
    EXPECT_EQ(copy.get(0), 10);
    EXPECT_EQ(copy.get(1), 20);
    EXPECT_EQ(copy.get(2), 30);

}

TEST(LinkedList, Assignment){

    LinkedList<int> a;

    a.append(10);
    a.append(20);

    LinkedList<int> b;

    b = a;

    EXPECT_EQ(b.get_length(), 2);
    EXPECT_EQ(b.get(0), 10);
    EXPECT_EQ(b.get(1), 20);

}

TEST(LinkedList, GetSubList){

    LinkedList<int> list;

    list.append(10);
    list.append(20);
    list.append(30);
    list.append(40);

    LinkedList<int> *sub = list.get_sub_list(1, 2);

    EXPECT_EQ(sub->get_length(), 2);
    EXPECT_EQ(sub->get(0), 20);
    EXPECT_EQ(sub->get(1), 30);

    delete sub;

}

TEST(LinkedList, Concat){

    LinkedList<int> a;

    a.append(10);
    a.append(20);

    LinkedList<int> b;

    b.append(30);
    b.append(40);

    LinkedList<int> *result = a.concat(&b);

    EXPECT_EQ(result->get_length(), 4);
    EXPECT_EQ(result->get(0), 10);
    EXPECT_EQ(result->get(1), 20);
    EXPECT_EQ(result->get(2), 30);
    EXPECT_EQ(result->get(3), 40);

    delete result;

}

TEST(LinkedList, OperatorPlus){

    LinkedList<int> a;

    a.append(10);
    a.append(20);

    LinkedList<int> b;

    b.append(30);
    b.append(40);

    LinkedList<int> result = a + b;

    EXPECT_EQ(result.get_length(), 4);
    EXPECT_EQ(result.get(0), 10);
    EXPECT_EQ(result.get(1), 20);
    EXPECT_EQ(result.get(2), 30);
    EXPECT_EQ(result.get(3), 40);

}

TEST(LinkedList, GetFromEmptyThrows){

    LinkedList<int> list;

    EXPECT_THROW(list.get_first(), empty_container);
    EXPECT_THROW(list.get_last(), empty_container);

}

TEST(LinkedList, InvalidIndexThrows){

    LinkedList<int> list;

    list.append(10);

    EXPECT_THROW(list.get(-1), index_out_of_range);
    EXPECT_THROW(list.get(1), index_out_of_range);
    EXPECT_THROW(list.remove_at(1), index_out_of_range);

}

TEST(TestListSequence, create){

    ListSequence<int> sequence;

    EXPECT_EQ(sequence.get_length(), 0);

}

TEST(TestListSequence, append){

    ListSequence<int> sequence;

    sequence.append(10);
    sequence.append(20);
    sequence.append(30);

    EXPECT_EQ(sequence.get_length(), 3);

    EXPECT_EQ(sequence.get_first(), 10);
    EXPECT_EQ(sequence.get_last(), 30);

}

TEST(TestListSequence, prepend){

    ListSequence<int> sequence;

    sequence.prepend(10);
    sequence.prepend(20);
    sequence.prepend(30);

    EXPECT_EQ(sequence.get_length(), 3);

    EXPECT_EQ(sequence.get(0), 30);
    EXPECT_EQ(sequence.get(1), 20);
    EXPECT_EQ(sequence.get(2), 10);

}

TEST(TestListSequence, get){

    ListSequence<int> sequence;

    sequence.append(10);
    sequence.append(20);
    sequence.append(30);

    EXPECT_EQ(sequence.get(0), 10);
    EXPECT_EQ(sequence.get(1), 20);
    EXPECT_EQ(sequence.get(2), 30);

}

TEST(TestListSequence, set){

    ListSequence<int> sequence;

    sequence.append(10);
    sequence.append(20);
    sequence.append(30);

    sequence.set(1, 100);

    EXPECT_EQ(sequence.get(1), 100);

}

TEST(TestListSequence, insert_at){

    ListSequence<int> sequence;

    sequence.append(10);
    sequence.append(30);

    sequence.insert_at(20, 1);

    EXPECT_EQ(sequence.get_length(), 3);

    EXPECT_EQ(sequence.get(0), 10);
    EXPECT_EQ(sequence.get(1), 20);
    EXPECT_EQ(sequence.get(2), 30);

}

TEST(TestListSequence, remove_middle){

    ListSequence<int> sequence;

    sequence.append(10);
    sequence.append(20);
    sequence.append(30);

    sequence.remove_at(1);

    EXPECT_EQ(sequence.get_length(), 2);

    EXPECT_EQ(sequence.get(0), 10);
    EXPECT_EQ(sequence.get(1), 30);

}

TEST(TestListSequence, remove_first){

    ListSequence<int> sequence;

    sequence.append(10);
    sequence.append(20);
    sequence.append(30);

    sequence.remove_at(0);

    EXPECT_EQ(sequence.get_length(), 2);

    EXPECT_EQ(sequence.get_first(), 20);
    EXPECT_EQ(sequence.get_last(), 30);

}

TEST(TestListSequence, remove_last){

    ListSequence<int> sequence;

    sequence.append(10);
    sequence.append(20);
    sequence.append(30);

    sequence.remove_at(2);

    EXPECT_EQ(sequence.get_length(), 2);

    EXPECT_EQ(sequence.get_first(), 10);
    EXPECT_EQ(sequence.get_last(), 20);

}

TEST(TestListSequence, operator_index){

    ListSequence<int> sequence;

    sequence.append(10);
    sequence.append(20);

    EXPECT_EQ(sequence[0], 10);
    EXPECT_EQ(sequence[1], 20);

}

TEST(TestListSequence, copy_constructor){

    ListSequence<int> sequence;

    sequence.append(10);
    sequence.append(20);
    sequence.append(30);

    ListSequence<int> copy(sequence);

    EXPECT_EQ(copy.get_length(), 3);

    EXPECT_EQ(copy.get(0), 10);
    EXPECT_EQ(copy.get(1), 20);
    EXPECT_EQ(copy.get(2), 30);

}

TEST(TestListSequence, get_sub_sequence){

    ListSequence<int> sequence;

    sequence.append(10);
    sequence.append(20);
    sequence.append(30);
    sequence.append(40);

    Sequence<int> *sub = sequence.get_sub_sequence(1, 2);

    EXPECT_EQ(sub->get_length(), 2);

    EXPECT_EQ(sub->get(0), 20);
    EXPECT_EQ(sub->get(1), 30);

    delete sub;

}

TEST(TestListSequence, concat){

    ListSequence<int> first;

    first.append(10);
    first.append(20);

    ListSequence<int> second;

    second.append(30);
    second.append(40);

    Sequence<int> *result = first.concat(&second);

    EXPECT_EQ(result->get_length(), 4);

    EXPECT_EQ(result->get(0), 10);
    EXPECT_EQ(result->get(1), 20);
    EXPECT_EQ(result->get(2), 30);
    EXPECT_EQ(result->get(3), 40);

    delete result;

}

size_t position_hash(Position pos){

    return pos.get_x() * 337 + pos.get_y() * 228;

}

TEST(TestHashTable, create){

    HashTable<Position, Cell> table(position_hash, 5);

    EXPECT_EQ(table.get_count(), 0);
    EXPECT_EQ(table.get_capacity(), 5);

}

TEST(TestHashTable, add_get){

    HashTable<Position, Cell> table(position_hash, 5);

    table.add(Position(1, 1), Cell::X);
    table.add(Position(2, 2), Cell::O);
    table.add(Position(3, 3), Cell::Empty);
    
    EXPECT_EQ(table.get(Position(1, 1)), Cell::X);
    EXPECT_EQ(table.get(Position(2, 2)), Cell::O);
    EXPECT_EQ(table.get(Position(3, 3)), Cell::Empty);

    EXPECT_THROW(table.add(Position(1, 1), Cell::O), key_already_exists);

}

TEST(TestHashTable, contains_key){

    HashTable<Position, Cell> table(position_hash, 5);

    table.add(Position(1, 1), Cell::X);
    table.add(Position(2, 2), Cell::O);
    table.add(Position(3, 3), Cell::Empty);
    
    EXPECT_TRUE(table.contains_key(Position(1, 1)));
    EXPECT_TRUE(table.contains_key(Position(2, 2)));
    EXPECT_TRUE(table.contains_key(Position(3, 3)));
    
    EXPECT_FALSE(table.contains_key(Position(1, 2)));
    EXPECT_FALSE(table.contains_key(Position(2, 1)));
    EXPECT_FALSE(table.contains_key(Position(3, 2)));

}

TEST(TestHashTable, remove){

    HashTable<Position, Cell> table(position_hash, 5);

    table.add(Position(1, 1), Cell::X);

    EXPECT_EQ(table.get_count(), 1);

    table.remove(Position(1, 1));
    EXPECT_THROW(table.get(Position(1, 1)), key_not_found);
    EXPECT_EQ(table.get_count(), 0);

}

TEST(TestHashTable, operator_kv_skobki){

    HashTable<Position, Cell> table(position_hash, 5);

    table.add(Position(1, 1), Cell::X);
    table[Position(1, 1)] = Cell::O;

    EXPECT_EQ(table.get_count(), 1);
    EXPECT_EQ(table.get(Position(1, 1)), Cell::O);

}

TEST(TestBoard, create){

    Board board(position_hash, 64);
    
    EXPECT_EQ(board.get_capacity(), 64);

}

TEST(TestBoard, make_move){

    Board board(position_hash, 9);
    board.make_move(Position(1, 1), Cell::X);
    
    EXPECT_EQ(board.get_cell(Position(1, 1)), Cell::X);
    EXPECT_EQ(board.get_cell(Position(2, 3)), Cell::Empty);

}

TEST(TestBoard, is_free){

    Board board(position_hash, 9);
    board.make_move(Position(1, 1), Cell::X);
    
    EXPECT_FALSE(board.is_free(Position(1, 1)));
    EXPECT_TRUE(board.is_free(Position(1, 2)));

}

TEST(TestBoard, remove_move){

    Board board(position_hash, 9);
    board.make_move(Position(1, 1), Cell::X);
    
    EXPECT_EQ(board.get_cell(Position(1, 1)), Cell::X);

    board.remove_move(Position(1, 1));
    
    EXPECT_TRUE(board.is_free(Position(1, 1)));

}

TEST(TestBoard, check_win_1){

    Board board(position_hash, 50);

    board.make_move(Position(0, 0), Cell::X);
    board.make_move(Position(1, 0), Cell::X);
    board.make_move(Position(2, 0), Cell::X);
    board.make_move(Position(3, 0), Cell::X);
    board.make_move(Position(4, 0), Cell::X);

    EXPECT_TRUE(board.check_win(Position(0, 0), Cell::X));
    EXPECT_TRUE(board.check_win(Position(1, 0), Cell::X));
    EXPECT_TRUE(board.check_win(Position(2, 0), Cell::X));
    EXPECT_TRUE(board.check_win(Position(3, 0), Cell::X));
    EXPECT_TRUE(board.check_win(Position(4, 0), Cell::X));

}

TEST(TestBoard, check_win_2){

    Board board(position_hash, 50);

    board.make_move(Position(0, 0), Cell::X);
    board.make_move(Position(0, 1), Cell::X);
    board.make_move(Position(0, 2), Cell::X);
    board.make_move(Position(0, 3), Cell::X);
    board.make_move(Position(0, 4), Cell::X);

    EXPECT_TRUE(board.check_win(Position(0, 0), Cell::X));
    EXPECT_TRUE(board.check_win(Position(0, 1), Cell::X));
    EXPECT_TRUE(board.check_win(Position(0, 2), Cell::X));
    EXPECT_TRUE(board.check_win(Position(0, 3), Cell::X));
    EXPECT_TRUE(board.check_win(Position(0, 4), Cell::X));

}

TEST(TestBoard, check_win_3){

    Board board(position_hash, 50);

    board.make_move(Position(0, 0), Cell::X);
    board.make_move(Position(1, 1), Cell::X);
    board.make_move(Position(2, 2), Cell::X);
    board.make_move(Position(3, 3), Cell::X);
    board.make_move(Position(4, 4), Cell::X);

    EXPECT_TRUE(board.check_win(Position(0, 0), Cell::X));
    EXPECT_TRUE(board.check_win(Position(1, 1), Cell::X));
    EXPECT_TRUE(board.check_win(Position(2, 2), Cell::X));
    EXPECT_TRUE(board.check_win(Position(3, 3), Cell::X));
    EXPECT_TRUE(board.check_win(Position(4, 4), Cell::X));

}

TEST(TestBoard, check_win_4){

    Board board(position_hash, 50);

    board.make_move(Position(0, 0), Cell::X);
    board.make_move(Position(-1, 1), Cell::X);
    board.make_move(Position(-2, 2), Cell::X);
    board.make_move(Position(-3, 3), Cell::X);
    board.make_move(Position(-4, 4), Cell::X);

    EXPECT_TRUE(board.check_win(Position(0, 0), Cell::X));
    EXPECT_TRUE(board.check_win(Position(-1, 1), Cell::X));
    EXPECT_TRUE(board.check_win(Position(-2, 2), Cell::X));
    EXPECT_TRUE(board.check_win(Position(-3, 3), Cell::X));
    EXPECT_TRUE(board.check_win(Position(-4, 4), Cell::X));

}

TEST(TestBoard, possible_move_1){

    Board board(position_hash, 9);
    board.make_move(Position(0, 0), Cell::X);
    
    EXPECT_TRUE(board.is_move_possible(Position(0, 1)));
    EXPECT_TRUE(board.is_move_possible(Position(0, -1)));
    EXPECT_TRUE(board.is_move_possible(Position(1, 0)));
    EXPECT_TRUE(board.is_move_possible(Position(-1, 0)));
    EXPECT_TRUE(board.is_move_possible(Position(1, 1)));
    EXPECT_TRUE(board.is_move_possible(Position(1, -1)));
    EXPECT_TRUE(board.is_move_possible(Position(-1, 1)));
    EXPECT_TRUE(board.is_move_possible(Position(-1, -1)));

    EXPECT_EQ(board.get_possible_moves_count(), 8);

}

TEST(TestBoard, possible_move_2){

    Board board(position_hash, 9);
    
    board.make_move(Position(0, 0), Cell::X);
    board.make_move(Position(1, 0), Cell::O);
    
    EXPECT_TRUE(board.is_move_possible(Position(0, 1)));
    EXPECT_TRUE(board.is_move_possible(Position(0, -1)));
    EXPECT_TRUE(board.is_move_possible(Position(-1, 0)));
    EXPECT_TRUE(board.is_move_possible(Position(1, 1)));
    EXPECT_TRUE(board.is_move_possible(Position(1, -1)));
    EXPECT_TRUE(board.is_move_possible(Position(-1, 1)));
    EXPECT_TRUE(board.is_move_possible(Position(-1, -1)));

    EXPECT_TRUE(board.is_move_possible(Position(2, 0)));
    EXPECT_TRUE(board.is_move_possible(Position(2, -1)));
    EXPECT_TRUE(board.is_move_possible(Position(2, 1)));

    EXPECT_EQ(board.get_possible_moves_count(), 10);

}

TEST(TestBoard, possible_move_3){

    Board board(position_hash, 9);
    
    board.make_move(Position(0, 0), Cell::X);
    board.make_move(Position(3, 3), Cell::O);
    
    EXPECT_TRUE(board.is_move_possible(Position(0, 1)));
    EXPECT_TRUE(board.is_move_possible(Position(0, -1)));
    EXPECT_TRUE(board.is_move_possible(Position(1, 0)));
    EXPECT_TRUE(board.is_move_possible(Position(-1, 0)));
    EXPECT_TRUE(board.is_move_possible(Position(1, 1)));
    EXPECT_TRUE(board.is_move_possible(Position(1, -1)));
    EXPECT_TRUE(board.is_move_possible(Position(-1, 1)));
    EXPECT_TRUE(board.is_move_possible(Position(-1, -1)));

    EXPECT_TRUE(board.is_move_possible(Position(3, 4)));
    EXPECT_TRUE(board.is_move_possible(Position(3, 2)));
    EXPECT_TRUE(board.is_move_possible(Position(4, 3)));
    EXPECT_TRUE(board.is_move_possible(Position(2, 3)));
    EXPECT_TRUE(board.is_move_possible(Position(4, 4)));
    EXPECT_TRUE(board.is_move_possible(Position(4, 2)));
    EXPECT_TRUE(board.is_move_possible(Position(2, 4)));
    EXPECT_TRUE(board.is_move_possible(Position(2, 2)));
    
    EXPECT_EQ(board.get_possible_moves_count(), 16);

}

TEST(TestBoard, remove_possible_moves_1){

    Board board(position_hash, 9);
    board.make_move(Position(1, 1), Cell::X);
    
    EXPECT_EQ(board.get_cell(Position(1, 1)), Cell::X);

    board.remove_move(Position(1, 1));
    
    EXPECT_TRUE(board.is_free(Position(1, 1)));
    EXPECT_TRUE(board.is_move_possible(Position(0, 0)));
    EXPECT_EQ(board.get_possible_moves_count(), 1);
    EXPECT_EQ(board.neighbour_count(Position(0, 0)), 0);

}

TEST(TestBoard, remove_possible_moves_2){

    Board board(position_hash, 9);

    board.make_move(Position(0, 0), Cell::X);
    board.make_move(Position(1, 0), Cell::O);

    EXPECT_TRUE(board.is_move_possible(Position(-1, 0)));
    EXPECT_TRUE(board.is_move_possible(Position(-1, 1)));
    EXPECT_TRUE(board.is_move_possible(Position(-1, -1)));
    EXPECT_TRUE(board.is_move_possible(Position(0, 1)));
    EXPECT_TRUE(board.is_move_possible(Position(1, 1)));
    EXPECT_TRUE(board.is_move_possible(Position(2, 1)));
    EXPECT_TRUE(board.is_move_possible(Position(2, 0)));
    EXPECT_TRUE(board.is_move_possible(Position(2, -1)));
    EXPECT_TRUE(board.is_move_possible(Position(1, -1)));
    EXPECT_TRUE(board.is_move_possible(Position(0, -1)));
    EXPECT_EQ(board.get_possible_moves_count(), 10);

    EXPECT_EQ(board.neighbour_count(Position(-1, 0)), 1);
    EXPECT_EQ(board.neighbour_count(Position(-1, 1)), 1);
    EXPECT_EQ(board.neighbour_count(Position(-1, -1)), 1);
    EXPECT_EQ(board.neighbour_count(Position(0, 1)), 2);
    EXPECT_EQ(board.neighbour_count(Position(1, 1)), 2);
    EXPECT_EQ(board.neighbour_count(Position(1, -1)), 2);
    EXPECT_EQ(board.neighbour_count(Position(0, -1)), 2);
    EXPECT_EQ(board.neighbour_count(Position(2, 1)), 1);
    EXPECT_EQ(board.neighbour_count(Position(2, 0)), 1);
    EXPECT_EQ(board.neighbour_count(Position(2, -1)), 1);

}

TEST(TestBoard, remove_possible_moves_3){

    Board board(position_hash, 9);

    board.make_move(Position(0, 0), Cell::X);
    board.make_move(Position(1, 0), Cell::O);
    board.remove_move(Position(1, 0));

    EXPECT_TRUE(board.is_move_possible(Position(-1, 0)));
    EXPECT_TRUE(board.is_move_possible(Position(-1, 1)));
    EXPECT_TRUE(board.is_move_possible(Position(-1, -1)));
    EXPECT_TRUE(board.is_move_possible(Position(0, 1)));
    EXPECT_TRUE(board.is_move_possible(Position(1, 1)));
    EXPECT_TRUE(board.is_move_possible(Position(1, -1)));
    EXPECT_TRUE(board.is_move_possible(Position(0, -1)));
    EXPECT_TRUE(board.is_move_possible(Position(1, 1)));
    EXPECT_EQ(board.get_possible_moves_count(), 8);

    EXPECT_EQ(board.neighbour_count(Position(-1, 0)), 1);
    EXPECT_EQ(board.neighbour_count(Position(-1, 1)), 1);
    EXPECT_EQ(board.neighbour_count(Position(-1, -1)), 1);
    EXPECT_EQ(board.neighbour_count(Position(0, 1)), 1);
    EXPECT_EQ(board.neighbour_count(Position(1, 1)), 1);
    EXPECT_EQ(board.neighbour_count(Position(1, -1)), 1);
    EXPECT_EQ(board.neighbour_count(Position(0, -1)), 1);
    EXPECT_EQ(board.neighbour_count(Position(1, 1)), 1);

}

TEST(TestBoard, remove_possible_moves_4){

    Board board(position_hash, 9);

    board.make_move(Position(0, 0), Cell::X);
    board.make_move(Position(1, 0), Cell::O);
    board.make_move(Position(1, 1), Cell::X);
    board.remove_move(Position(1, 0));

    EXPECT_TRUE(board.is_move_possible(Position(-1, 0)));
    EXPECT_TRUE(board.is_move_possible(Position(-1, 1)));
    EXPECT_TRUE(board.is_move_possible(Position(-1, -1)));
    EXPECT_TRUE(board.is_move_possible(Position(0, 1)));
    EXPECT_TRUE(board.is_move_possible(Position(0, 2)));
    EXPECT_TRUE(board.is_move_possible(Position(1, 2)));
    EXPECT_TRUE(board.is_move_possible(Position(2, 2)));
    EXPECT_TRUE(board.is_move_possible(Position(2, 1)));
    EXPECT_TRUE(board.is_move_possible(Position(2, 0)));
    EXPECT_TRUE(board.is_move_possible(Position(1, 0)));
    EXPECT_TRUE(board.is_move_possible(Position(1, -1)));
    EXPECT_TRUE(board.is_move_possible(Position(0, -1)));

    EXPECT_EQ(board.get_possible_moves_count(), 12);

    EXPECT_EQ(board.neighbour_count(Position(-1, 0)), 1);
    EXPECT_EQ(board.neighbour_count(Position(-1, 1)), 1);
    EXPECT_EQ(board.neighbour_count(Position(-1, -1)), 1);
    EXPECT_EQ(board.neighbour_count(Position(0, 1)), 2);
    EXPECT_EQ(board.neighbour_count(Position(0, 2)), 1);
    EXPECT_EQ(board.neighbour_count(Position(1, 2)), 1);
    EXPECT_EQ(board.neighbour_count(Position(2, 2)), 1);
    EXPECT_EQ(board.neighbour_count(Position(2, 1)), 1);
    EXPECT_EQ(board.neighbour_count(Position(2, 0)), 1);
    EXPECT_EQ(board.neighbour_count(Position(1, 0)), 2);
    EXPECT_EQ(board.neighbour_count(Position(1, -1)), 1);
    EXPECT_EQ(board.neighbour_count(Position(0, -1)), 1);

}

TEST(TestBoard, remove_possible_moves_5){

    Board board(position_hash, 9);

    board.make_move(Position(-1, 0), Cell::O);
    board.make_move(Position(0, 0), Cell::X);
    board.make_move(Position(1, 0), Cell::O);
    board.make_move(Position(-1, 1), Cell::X);
    board.make_move(Position(0, 1), Cell::O);
    board.make_move(Position(1, 1), Cell::X);
    board.make_move(Position(-1, 2), Cell::O);
    board.make_move(Position(0, 2), Cell::X);
    board.make_move(Position(1, 2), Cell::O);

    board.remove_move(Position(1, 1));

    EXPECT_TRUE(board.is_move_possible(Position(1, 1)));

    EXPECT_FALSE(board.is_move_possible(Position(-1, 0)));
    EXPECT_FALSE(board.is_move_possible(Position(0, 0)));
    EXPECT_FALSE(board.is_move_possible(Position(1, 0)));
    EXPECT_FALSE(board.is_move_possible(Position(-1, 1)));
    EXPECT_FALSE(board.is_move_possible(Position(0, 1)));
    EXPECT_FALSE(board.is_move_possible(Position(-1, 2)));
    EXPECT_FALSE(board.is_move_possible(Position(0, 2)));
    EXPECT_FALSE(board.is_move_possible(Position(1, 2)));

    EXPECT_EQ(board.get_possible_moves_count(), 17);

}

TEST(TestBoard, get_keys_empty){

    HashTable<Position, Cell> table(position_hash, 9);

    EXPECT_EQ(table.get_keys(), ListSequence<Position>{});

}

TEST(TestBoard, get_keys_from_empty_board){

    Board board(position_hash, 9);

    EXPECT_EQ(board.get_possible_moves(), ListSequence<Position>{Position(0, 0)});

}

TEST(TestBoard, get_keys_from_not_empty_board){

    Board board(position_hash, 9);
    board.make_move(Position(0, 0), Cell::X);

    ListSequence<Position> poss_moves = board.get_possible_moves();
    size_t len = poss_moves.get_length();

    for (size_t i = 0; i < len; ++i){

        EXPECT_TRUE(board.is_move_possible(poss_moves[i]));

    }

}

TEST(TestBot, evaluate_pattern_1){

    Board board(position_hash, 9);
    Bot bot(Cell::X);

    board.make_move(Position(0, 0), Cell::X);
    board.make_move(Position(0, 1), Cell::X);

    EXPECT_EQ(bot.evaluate_pattern(board, Position(0, 2), Cell::X), 10000 + 6);

}

TEST(TestBot, evaluate_pattern_2){

    Board board(position_hash, 9);
    Bot bot(Cell::X);

    board.make_move(Position(0, 0), Cell::X);
    board.make_move(Position(0, 1), Cell::X);
    board.make_move(Position(1, 1), Cell::O);

    EXPECT_EQ(bot.evaluate_pattern(board, Position(0, 2), Cell::X), 10000 + 6 - 1);
    
}

TEST(TestBot, evaluate_pattern_3){

    Board board(position_hash, 9);
    Bot bot(Cell::X);

    board.make_move(Position(0, 0), Cell::X);
    board.make_move(Position(0, 1), Cell::X);
    board.make_move(Position(1, 1), Cell::X);

    EXPECT_EQ(bot.evaluate_pattern(board, Position(1, 0), Cell::X), 3 * 100 + 2);
    
}

TEST(TestBot, evaluate_pattern_4){

    Board board(position_hash, 9);
    Bot bot(Cell::X);

    board.make_move(Position(0, 0), Cell::X);
    board.make_move(Position(0, 1), Cell::X);
    board.make_move(Position(1, 1), Cell::X);

    board.make_move(Position(0, -1), Cell::O);
    board.make_move(Position(-1, 0), Cell::O);
    board.make_move(Position(-1, 2), Cell::O);
    board.make_move(Position(1, 2), Cell::O);
    board.make_move(Position(2, 1), Cell::O);
    board.make_move(Position(2, 0), Cell::O);
    board.make_move(Position(2, -1), Cell::O);
    board.make_move(Position(1, -1), Cell::O);

    EXPECT_EQ(bot.evaluate_pattern(board, Position(1, 0), Cell::X), 0);
    
}

TEST(TestBot, evaluate_move_1){

    Board board(position_hash, 9);
    Bot bot(Cell::X);

    EXPECT_EQ(bot.evaluate_move(board, Position(0, 0), Cell::X), 16);
    
}

TEST(TestBot, evaluate_move_2){

    Board board(position_hash, 9);
    Bot bot(Cell::X);

    board.make_move(Position(0, 0), Cell::X);
    board.make_move(Position(0, 1), Cell::X);
    board.make_move(Position(1, 1), Cell::O);

    EXPECT_EQ(bot.evaluate_move(board, Position(0, 2), Cell::X), 10110);
    
}

TEST(TestBot, evaluate_move_3){

    Board board(position_hash, 9);
    Bot bot(Cell::X);

    board.make_move(Position(0, 0), Cell::X);
    board.make_move(Position(0, 1), Cell::X);
    board.make_move(Position(1, 1), Cell::X);

    EXPECT_EQ(bot.evaluate_move(board, Position(1, 0), Cell::X), 307);
    
}

TEST(TestBot, evaluate_move_4){

    Board board(position_hash, 9);
    Bot bot(Cell::X);

    board.make_move(Position(0, 0), Cell::X);
    board.make_move(Position(0, 1), Cell::X);
    board.make_move(Position(1, 1), Cell::X);

    board.make_move(Position(0, -1), Cell::O);
    board.make_move(Position(-1, 0), Cell::O);
    board.make_move(Position(-1, 2), Cell::O);
    board.make_move(Position(1, 2), Cell::O);
    board.make_move(Position(2, 1), Cell::O);
    board.make_move(Position(2, 0), Cell::O);
    board.make_move(Position(2, -1), Cell::O);
    board.make_move(Position(1, -1), Cell::O);

    EXPECT_EQ(bot.evaluate_move(board, Position(1, 0), Cell::X), 10030);
    
}

TEST(TestBot, evaluate_1){

    Board board(position_hash, 9);
    Bot bot(Cell::X);

    EXPECT_EQ(bot.evaluate(board), 0);
    
}

TEST(TestBot, evaluate_2){

    Board board(position_hash, 9);
    Bot bot(Cell::X);

    board.make_move(Position(0, 0), Cell::X);
    board.make_move(Position(0, 1), Cell::X);
    board.make_move(Position(1, 1), Cell::O);

    EXPECT_EQ(bot.evaluate(board), 20394);
    
}

TEST(TestBot, evaluate_3){

    Board board(position_hash, 9);
    Bot bot(Cell::X);

    board.make_move(Position(0, 0), Cell::X);
    board.make_move(Position(0, 1), Cell::X);
    board.make_move(Position(1, 1), Cell::X);

    EXPECT_EQ(bot.evaluate(board), 61182);
    
}

TEST(TestBot, evaluate_4){

    Board board(position_hash, 9);
    Bot bot(Cell::X);

    board.make_move(Position(0, 0), Cell::X);
    board.make_move(Position(0, 1), Cell::X);
    board.make_move(Position(1, 1), Cell::X);

    board.make_move(Position(0, -1), Cell::O);
    board.make_move(Position(-1, 0), Cell::O);
    board.make_move(Position(-1, 2), Cell::O);
    board.make_move(Position(1, 2), Cell::O);
    board.make_move(Position(2, 1), Cell::O);
    board.make_move(Position(2, 0), Cell::O);
    board.make_move(Position(2, -1), Cell::O);
    board.make_move(Position(1, -1), Cell::O);

    EXPECT_EQ(bot.evaluate(board), -4069374);
    
}


TEST(TestBot, minimax_1){

    Board board(position_hash, 9);
    Bot bot(Cell::X);

    EXPECT_EQ(bot.minimax(board, 0, -INF, INF, true), 0);
    
}

TEST(TestBot, minimax_2){

    Board board(position_hash, 9);
    Bot bot(Cell::X);

    board.make_move(Position(0, 0), Cell::X);
    board.make_move(Position(0, 1), Cell::X);
    board.make_move(Position(1, 1), Cell::O);

    ListSequence<Position> moves = board.get_possible_moves();

    long long int expected = -INF;

    for (size_t i = 0; i < moves.get_length(); ++i){

        Position pos = moves[i];

        board.make_move(pos, Cell::X);
        expected = std::max(expected, bot.evaluate(board));
        board.remove_move(pos);

    }

    EXPECT_EQ(bot.minimax(board, 1, -INF, INF, true), expected);

}

TEST(TestBot, minimax_3){

    Board board(position_hash, 9);
    Bot bot(Cell::X);

    board.make_move(Position(0, 0), Cell::X);
    board.make_move(Position(0, 1), Cell::X);
    board.make_move(Position(1, 1), Cell::O);

    ListSequence<Position> moves = board.get_possible_moves();

    long long int expected = INF;

    for (size_t i = 0; i < moves.get_length(); ++i){

        Position pos = moves[i];

        board.make_move(pos, Cell::O);
        expected = std::min(expected, bot.evaluate(board));
        board.remove_move(pos);

    }

    EXPECT_EQ(bot.minimax(board, 1, -INF, INF, false), expected);

}

TEST(TestBot, minimax_4){

    Board board(position_hash, 9);
    Bot bot(Cell::X);

    board.make_move(Position(0, 0), Cell::X);
    board.make_move(Position(1, 0), Cell::X);
    board.make_move(Position(2, 0), Cell::X);
    board.make_move(Position(3, 0), Cell::X);

    EXPECT_EQ(bot.minimax(board, 1, -INF, INF, true), WIN);

}

TEST(TestBot, minimax_5){

    Board board(position_hash, 9);
    Bot bot(Cell::X);

    board.make_move(Position(0, 0), Cell::O);
    board.make_move(Position(1, 0), Cell::O);
    board.make_move(Position(2, 0), Cell::O);
    board.make_move(Position(3, 0), Cell::O);

    EXPECT_EQ(bot.minimax(board, 1, -INF, INF, false), LOSE);

}

TEST(TestBot, find_best_move_1){

    Board board(position_hash, 9);
    Bot bot(Cell::X);

    EXPECT_EQ(bot.find_best_move(board), Position(0, 0));

}

TEST(TestBot, find_best_move_2){

    Board board(position_hash, 9);
    Bot bot(Cell::X);

    board.make_move(Position(0, 0), Cell::X);
    board.make_move(Position(1, 0), Cell::X);
    board.make_move(Position(2, 0), Cell::X);
    board.make_move(Position(3, 0), Cell::X);

    board.make_move(Position(-1, 0), Cell::O);

    EXPECT_EQ(bot.find_best_move(board), Position(4, 0));

}

TEST(TestBot, find_best_move_3){

    Board board(position_hash, 9);
    Bot bot(Cell::X);

    board.make_move(Position(0, 0), Cell::O);
    board.make_move(Position(1, 0), Cell::O);
    board.make_move(Position(2, 0), Cell::O);
    board.make_move(Position(3, 0), Cell::O);
    board.make_move(Position(10, 10), Cell::O);
    board.make_move(Position(11, 10), Cell::O);
    board.make_move(Position(-1, 0), Cell::X);

    EXPECT_EQ(bot.find_best_move(board), Position(4, 0));

}

TEST(TestBot, find_best_move_4){

    Board board(position_hash, 9);
    Bot bot(Cell::X);

    board.make_move(Position(0, 0), Cell::X);
    board.make_move(Position(1, 1), Cell::X);
    board.make_move(Position(2, 2), Cell::X);
    board.make_move(Position(3, 3), Cell::X);

    board.make_move(Position(-1, -1), Cell::O);

    EXPECT_EQ(bot.find_best_move(board), Position(4, 4));

}
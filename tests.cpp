#include <gtest/gtest.h>

#include "includes/LinkedList.hpp"
#include "includes/ListSequence.hpp"
#include "includes/HashTable.hpp"
#include "includes/Position.hpp"
#include "includes/Cell.hpp"

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
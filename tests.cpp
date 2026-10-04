#include <gtest/gtest.h>

#include "includes/LinkedList.hpp"
#include "includes/ListSequence.hpp"

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
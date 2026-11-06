#include <gtest/gtest.h>

#include "Includes/Tree.hpp"
#include "Includes/Exception.hpp"

TEST(TestTree, create_empty){

    Tree<int> tree;

    EXPECT_THROW(tree.get_root(), root_is_empty);

}

TEST(TestTree, create_with_val){

    Tree<int> tree(10);

    EXPECT_EQ(tree.get_root(), 10);
    EXPECT_TRUE(tree.find(10));

}

TEST(TestTree, add){

    Tree<int> tree;

    tree.add(10);
    tree.add(5);
    tree.add(15);
    tree.add(3);
    tree.add(7);

    EXPECT_EQ(tree.get_root(), 10);
    EXPECT_TRUE(tree.find(5));
    EXPECT_TRUE(tree.find(15));
    EXPECT_TRUE(tree.find(3));
    EXPECT_TRUE(tree.find(7));

}

TEST(TestTree, find){

    Tree<int> tree;

    tree.add(10);
    tree.add(5);
    tree.add(15);

    EXPECT_TRUE(tree.find(10));
    EXPECT_TRUE(tree.find(5));
    EXPECT_TRUE(tree.find(15));
    EXPECT_FALSE(tree.find(100));
    EXPECT_FALSE(tree.find(-5));

}

TEST(TestTree, remove_empty){

    Tree<int> tree;

    EXPECT_FALSE(tree.remove(10));

}

TEST(TestTree, remove_not_found){

    Tree<int> tree;

    tree.add(10);
    tree.add(5);
    tree.add(15);

    EXPECT_FALSE(tree.remove(100));
    EXPECT_TRUE(tree.find(10));
    EXPECT_TRUE(tree.find(5));
    EXPECT_TRUE(tree.find(15));

}

TEST(TestTree, remove_leaf){

    Tree<int> tree;

    tree.add(10);
    tree.add(5);
    tree.add(15);

    EXPECT_TRUE(tree.remove(5));

    EXPECT_FALSE(tree.find(5));
    EXPECT_TRUE(tree.find(10));
    EXPECT_TRUE(tree.find(15));

}

TEST(TestTree, remove_with_left_child){

    Tree<int> tree;

    tree.add(10);
    tree.add(5);
    tree.add(3);

    EXPECT_TRUE(tree.remove(5));

    EXPECT_FALSE(tree.find(5));
    EXPECT_TRUE(tree.find(3));
    EXPECT_TRUE(tree.find(10));

    EXPECT_TRUE(tree.remove(3));
    EXPECT_FALSE(tree.find(3));

}

TEST(TestTree, remove_with_right_child){

    Tree<int> tree;

    tree.add(10);
    tree.add(15);
    tree.add(20);

    EXPECT_TRUE(tree.remove(15));

    EXPECT_FALSE(tree.find(15));
    EXPECT_TRUE(tree.find(20));
    EXPECT_TRUE(tree.find(10));

    EXPECT_TRUE(tree.remove(20));
    EXPECT_FALSE(tree.find(20));

}

TEST(TestTree, remove_with_two_children){

    Tree<int> tree;

    tree.add(20);
    tree.add(10);
    tree.add(30);
    tree.add(5);
    tree.add(15);
    tree.add(12);
    tree.add(17);

    EXPECT_TRUE(tree.remove(10));
    EXPECT_FALSE(tree.find(10));

    EXPECT_TRUE(tree.find(20));
    EXPECT_TRUE(tree.find(30));
    EXPECT_TRUE(tree.find(5));
    EXPECT_TRUE(tree.find(15));
    EXPECT_TRUE(tree.find(12));
    EXPECT_TRUE(tree.find(17));

}

TEST(TestTree, remove_single_root){

    Tree<int> tree(10);

    EXPECT_TRUE(tree.remove(10));

    EXPECT_FALSE(tree.find(10));
    EXPECT_THROW(tree.get_root(), root_is_empty);

}

TEST(TestTree, remove_root_with_one_child){

    Tree<int> tree;

    tree.add(10);
    tree.add(5);

    EXPECT_TRUE(tree.remove(10));

    EXPECT_EQ(tree.get_root(), 5);
    EXPECT_FALSE(tree.find(10));
    EXPECT_TRUE(tree.find(5));

}

TEST(TestTree, remove_root_with_two_children){

    Tree<int> tree;

    tree.add(10);
    tree.add(5);
    tree.add(15);
    tree.add(3);
    tree.add(8);

    EXPECT_TRUE(tree.remove(10));

    EXPECT_EQ(tree.get_root(), 5);
    EXPECT_FALSE(tree.find(10));
    EXPECT_TRUE(tree.find(5));
    EXPECT_TRUE(tree.find(15));
    EXPECT_TRUE(tree.find(3));
    EXPECT_TRUE(tree.find(8));

}

TEST(TestTree, duplicates){

    Tree<int> tree;

    tree.add(10);
    tree.add(5);
    tree.add(5);
    tree.add(5);

    EXPECT_TRUE(tree.remove(5));
    EXPECT_TRUE(tree.find(5));

    EXPECT_TRUE(tree.remove(5));
    EXPECT_TRUE(tree.find(5));

    EXPECT_TRUE(tree.remove(5));
    EXPECT_FALSE(tree.find(5));

    EXPECT_FALSE(tree.remove(5));
    EXPECT_TRUE(tree.find(10));

}

TEST(TestTree, remove_all){

    Tree<int> tree;

    tree.add(10);
    tree.add(5);
    tree.add(15);
    tree.add(3);
    tree.add(7);

    EXPECT_TRUE(tree.remove(10));
    EXPECT_TRUE(tree.remove(5));
    EXPECT_TRUE(tree.remove(15));
    EXPECT_TRUE(tree.remove(3));
    EXPECT_TRUE(tree.remove(7));

    EXPECT_FALSE(tree.find(10));
    EXPECT_FALSE(tree.find(5));
    EXPECT_FALSE(tree.find(15));
    EXPECT_FALSE(tree.find(3));
    EXPECT_FALSE(tree.find(7));

    EXPECT_THROW(tree.get_root(), root_is_empty);

}

TEST(TestTree, string){

    Tree<std::string> tree;

    tree.add("banana");
    tree.add("apple");
    tree.add("cccccc");

    EXPECT_TRUE(tree.find("banana"));
    EXPECT_TRUE(tree.find("apple"));
    EXPECT_TRUE(tree.find("cccccc"));

    EXPECT_FALSE(tree.find("brbrbr"));

    EXPECT_TRUE(tree.remove("apple"));
    EXPECT_FALSE(tree.find("apple"));

}
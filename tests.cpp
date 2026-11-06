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

TEST(TestTree, map){

    Tree<int> tree;

    tree.add(10);
    tree.add(5);
    tree.add(15);

    Tree<int> res = tree.map([](int x){return x + 2;});

    EXPECT_TRUE(res.find(12));
    EXPECT_TRUE(res.find(7));
    EXPECT_TRUE(res.find(17));
    EXPECT_EQ(res.get_root(), 12);

}

TEST(TestTree, map_empty){

    Tree<int> tree;
    Tree<int> res = tree.map([](int x){return x + 10;});

    EXPECT_THROW(res.get_root(), root_is_empty);

}

TEST(TestTree, where){

    Tree<int> tree;

    tree.add(10);
    tree.add(5);
    tree.add(15);
    tree.add(3);
    tree.add(20);

    Tree<int> res = tree.where([](int x){return x > 10;});

    EXPECT_TRUE(res.find(15));
    EXPECT_TRUE(res.find(20));

    EXPECT_FALSE(res.find(10));
    EXPECT_FALSE(res.find(5));
    EXPECT_FALSE(res.find(3));

    EXPECT_EQ(tree.get_root(), 10);
    EXPECT_EQ(res.get_root(), 15);

}

TEST(TestTree, where_empty){

    Tree<int> tree;
    Tree<int> res = tree.where([](int x){return x > 10;});

    EXPECT_THROW(res.get_root(), root_is_empty);

}

TEST(TestTree, where_no_matches){

    Tree<int> tree;

    tree.add(10);
    tree.add(5);
    tree.add(15);

    Tree<int> res = tree.where([](int x){return x > 100;});

    EXPECT_THROW(res.get_root(), root_is_empty);

}

TEST(TestTree, reduce_sum){

    Tree<int> tree;

    tree.add(10);
    tree.add(5);
    tree.add(15);

    int res = tree.reduce(0, [](int a, int b){return a + b;});

    EXPECT_EQ(res, 30);

}

TEST(TestTree, reduce_mult){

    Tree<int> tree;

    tree.add(2);
    tree.add(3);
    tree.add(4);

    int res = tree.reduce(1, [](int a, int b){return a * b;});

    EXPECT_EQ(res, 24);

}

TEST(TestTree, reduce_empty){

    Tree<int> tree;

    int res = tree.reduce(1, [](int a, int b){return a + b;});

    EXPECT_EQ(res, 1);

}

TEST(TestTree, reduce_2){

    Tree<int> tree;

    tree.add(5);
    tree.add(3);
    tree.add(7);

    int res = tree.reduce(0, [](int a, int b){return a * 10 + b;});

    EXPECT_EQ(res, 537);

}

TEST(TestTree, reduce_different_type){

    Tree<int> tree;

    tree.add(10);
    tree.add(20);
    tree.add(30);

    std::string res = tree.reduce(std::string(""), [](const std::string& a, int b){

        return a + std::to_string(b) + " ";

    });

    EXPECT_EQ(res, "10 20 30 ");

}

TEST(TestTree, get_subtree){

    Tree<int> tree;

    tree.add(10);
    tree.add(5);
    tree.add(15);
    tree.add(3);
    tree.add(20);

    Tree<int> res = tree.get_subtree(5);

    EXPECT_TRUE(res.find(5));
    EXPECT_TRUE(res.find(3));
    EXPECT_EQ(res.get_root(), 5);

    EXPECT_EQ(tree.get_root(), 10);

}

TEST(TestTree, get_subtree_1){

    Tree<int> tree;

    tree.add(10);
    tree.add(5);
    tree.add(15);
    tree.add(3);
    tree.add(20);

    Tree<int> res = tree.get_subtree(3);

    EXPECT_TRUE(res.find(3));
    EXPECT_EQ(res.get_root(), 3);
    
    EXPECT_EQ(tree.get_root(), 10);

}

TEST(TestTree, get_subtree_empty){

    Tree<int> tree;

    tree.add(10);
    tree.add(5);
    tree.add(15);
    tree.add(3);
    tree.add(20);

    Tree<int> res = tree.get_subtree(300);

    EXPECT_THROW(res.get_root(), root_is_empty);
    
    EXPECT_EQ(tree.get_root(), 10);

}

TEST(TestTree, get_subtree_tree){

    Tree<int> tree;

    tree.add(10);
    tree.add(5);
    tree.add(15);
    tree.add(3);
    tree.add(20);

    Tree<int> res = tree.get_subtree(10);

    EXPECT_EQ(res.get_root(), 10);
    EXPECT_TRUE(res.find(10));
    EXPECT_TRUE(res.find(5));
    EXPECT_TRUE(res.find(15));
    EXPECT_TRUE(res.find(3));
    EXPECT_TRUE(res.find(20));
    
    EXPECT_EQ(tree.get_root(), 10);

}

TEST(TestTree, to_string_empty){

    Tree<int> tree;

    EXPECT_EQ(tree.to_string(), "");

}

TEST(TestTree, to_string_single){

    Tree<int> tree(10);

    EXPECT_EQ(tree.to_string(), "10 ");

}

TEST(TestTree, to_string){

    Tree<int> tree;

    tree.add(10);
    tree.add(5);
    tree.add(15);
    tree.add(3);
    tree.add(7);
    tree.add(20);

    EXPECT_EQ(tree.to_string(), "10 5 3 7 15 20 ");

}

TEST(TestTree, to_string_no_change){

    Tree<int> tree;

    tree.add(10);
    tree.add(5);
    tree.add(15);

    std::string res = tree.to_string();

    EXPECT_EQ(res, "10 5 15 ");

    EXPECT_EQ(tree.get_root(), 10);
    EXPECT_TRUE(tree.find(5));
    EXPECT_TRUE(tree.find(15));

}

TEST(TestTree, to_string_duplicates){

    Tree<int> tree;

    tree.add(10);
    tree.add(5);
    tree.add(5);
    tree.add(15);
    tree.add(10);

    EXPECT_EQ(tree.to_string(), "10 5 5 10 15 ");

}

TEST(TestTree, to_string_negative){

    Tree<int> tree;

    tree.add(0);
    tree.add(-10);
    tree.add(10);
    tree.add(-20);
    tree.add(-5);

    EXPECT_EQ(tree.to_string(), "0 -10 -20 -5 10 ");

}

TEST(TestTree, to_string_strings){

    Tree<std::string> tree;

    tree.add("banana");
    tree.add("apple");
    tree.add("cherry");

    EXPECT_EQ(tree.to_string(), "banana apple cherry ");

}

TEST(TestTree, to_string_after_remove){

    Tree<int> tree;

    tree.add(10);
    tree.add(5);
    tree.add(15);
    tree.add(3);
    tree.add(7);

    EXPECT_TRUE(tree.remove(5));

    EXPECT_EQ(tree.to_string(), "10 3 7 15 ");
    EXPECT_TRUE(tree.find(3));
    EXPECT_TRUE(tree.find(7));

}
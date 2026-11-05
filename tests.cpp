#include <gtest/gtest.h>

#include "Includes/Tree.hpp"
#include "Includes/Exception.hpp"

TEST(Tree, CreateEmpty){

    Tree<int> tree;

    EXPECT_THROW(tree.get_root(), root_is_empty);

}
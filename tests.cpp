#include <gtest/gtest.h>

#include "includes/UniquePtr.hpp"

TEST(TestUniquePtr, create){

    UniquePtr<int> a(new int (5));

    EXPECT_TRUE(a.get());
    EXPECT_EQ(*a, 5);

    UniquePtr<int> b(new int (10));
    UniquePtr<int> c(std::move(b));

    EXPECT_EQ(b.get(), nullptr);
    EXPECT_EQ(*c, 10);

}

TEST(TestUniquePtr, check_methods){

    UniquePtr<int> a(new int (5));

    EXPECT_TRUE(a.get());
    EXPECT_EQ(*a, 5);

    a.reset(new int(10));

    EXPECT_EQ(*a, 10);

    int *b = a.release();
    
    EXPECT_FALSE(a.get());
    EXPECT_EQ(*b, 10);

    delete b;

}
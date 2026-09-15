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

TEST(TestUniquePtr, check_operators){

    UniquePtr<int> a(new int (5));
    UniquePtr<int> b;

    b = std::move(a);

    EXPECT_EQ(*b.get(), 5);
    EXPECT_EQ(*b, 5);
    
    class Test{

        private:

            int val;

        public:

            Test(int value) : val(value){}

            int get(){

                return val;

            }

    };

    UniquePtr<Test> c(new Test (10));

    EXPECT_EQ(c->get(), 10);

}
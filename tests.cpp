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


    UniquePtr<int[]> arr(new int [3]);

    arr[0] = 0;
    arr[1] = 1;
    arr[2] = 2;

    int* r = arr.get();

    EXPECT_EQ(r[0], 0);
    EXPECT_EQ(r[1], 1);
    EXPECT_EQ(r[2], 2);

    UniquePtr<int[]> arrr(new int [2]);
    arrr[0] = 0;
    arrr[1] = 1;
    UniquePtr<int[]> arrrr(std::move(arrr));

    EXPECT_EQ(arrr.get(), nullptr);
    EXPECT_EQ(arrrr[0], 0);
    EXPECT_EQ(arrrr[1], 1);

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


    UniquePtr<int[]> arr(new int [3]);
    int* ar = new int [2];
    
    ar[0] = 0;
    ar[1] = 1; 

    arr[0] = 10;
    arr[1] = 11;
    arr[2] = 12;

    arr.reset(ar);

    EXPECT_EQ(arr[0], 0);
    EXPECT_EQ(arr[1], 1);
    
    int *r = arr.release();

    EXPECT_FALSE(arr.get());
    EXPECT_EQ(r[0], 0);
    EXPECT_EQ(r[1], 1);

    delete[] r;

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
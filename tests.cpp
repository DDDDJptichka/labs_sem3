#include <gtest/gtest.h>
#include <utility>

#include "includes/UniquePtr.hpp"
#include "includes/SharedPtr.hpp"

class TestObj{
    
    private:
    
        int val;

    public:
        
        TestObj(int value) : val(value) {}

        int get() {
            
            return val;
    
        }
};

TEST(TestUniquePtr, Constructor) {

    UniquePtr<int> a(new int(5));

    EXPECT_TRUE(a.get());
    EXPECT_EQ(*a, 5);

}

TEST(TestUniquePtr, MoveConstructor) {

    UniquePtr<int> a(new int(10));
    UniquePtr<int> b(std::move(a));

    EXPECT_EQ(a.get(), nullptr);
    EXPECT_EQ(*b, 10);

}

TEST(TestUniquePtrArray, Constructor) {

    UniquePtr<int[]> arr(new int[3]);

    arr[0] = 0;
    arr[1] = 1;
    arr[2] = 2;

    EXPECT_EQ(arr[0], 0);
    EXPECT_EQ(arr[1], 1);
    EXPECT_EQ(arr[2], 2);

}

TEST(TestUniquePtrArray, MoveConstructor) {

    UniquePtr<int[]> arr(new int[2]);

    arr[0] = 0;
    arr[1] = 1;

    UniquePtr<int[]> arr2(std::move(arr));

    EXPECT_EQ(arr.get(), nullptr);
    EXPECT_EQ(arr2[0], 0);
    EXPECT_EQ(arr2[1], 1);

}

TEST(TestUniquePtr, Get) {

    UniquePtr<int> a(new int(5));

    int* ptr = a.get();

    EXPECT_TRUE(ptr);
    EXPECT_EQ(*ptr, 5);

}

TEST(TestUniquePtrArray, Get) {

    UniquePtr<int[]> arr(new int[3]);

    arr[0] = 0;
    arr[1] = 1;
    arr[2] = 2;

    int* ptr = arr.get();

    EXPECT_EQ(ptr[0], 0);
    EXPECT_EQ(ptr[1], 1);
    EXPECT_EQ(ptr[2], 2);

}

TEST(TestUniquePtr, Reset) {

    UniquePtr<int> a(new int(5));

    a.reset(new int(10));

    EXPECT_EQ(*a, 10);

}

TEST(TestUniquePtrArray, Reset) {

    UniquePtr<int[]> arr(new int[3]);

    int* ar = new int[2]{0, 1};

    arr.reset(ar);

    EXPECT_EQ(arr[0], 0);
    EXPECT_EQ(arr[1], 1);

}

TEST(TestUniquePtr, Release) {

    UniquePtr<int> a(new int(10));

    int* ptr = a.release();

    EXPECT_EQ(a.get(), nullptr);
    EXPECT_EQ(*ptr, 10);

    delete ptr;

}

TEST(TestUniquePtrArray, Release) {

    UniquePtr<int[]> arr(new int[2]{0, 1});

    int* ptr = arr.release();

    EXPECT_EQ(arr.get(), nullptr);
    EXPECT_EQ(ptr[0], 0);
    EXPECT_EQ(ptr[1], 1);

    delete[] ptr;

}

TEST(TestUniquePtr, MoveAssignment) {

    UniquePtr<int> a(new int(5));
    UniquePtr<int> b;

    b = std::move(a);

    EXPECT_EQ(a.get(), nullptr);
    EXPECT_EQ(*b, 5);

}

TEST(TestUniquePtr, DereferenceOperator) {

    UniquePtr<int> a(new int(5));

    EXPECT_EQ(*a, 5);

}

TEST(TestUniquePtr, ArrowOperator) {

    UniquePtr<TestObj> a(new TestObj(10));

    EXPECT_EQ(a->get(), 10);

}

TEST(TestUniquePtrArray, IndexOperator) {

    UniquePtr<int[]> arr(new int[3]{1, 2, 3});

    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 3);

}

TEST(TestUniquePtr, MakeUnique) {

    auto a = makeUnique<int>(5);

    EXPECT_EQ(*a, 5);

}

TEST(TestUniquePtrArray, MakeUniqueArray) {

    auto arr = makeUniqueArray<int>(3);

    arr[0] = 0;
    arr[1] = 1;
    arr[2] = 2;

    EXPECT_EQ(arr[0], 0);
    EXPECT_EQ(arr[1], 1);
    EXPECT_EQ(arr[2], 2);

}

TEST(TestSharedPtr, Constructor) {

    SharedPtr<int> a(new int(10));

    EXPECT_EQ(*a, 10);
    EXPECT_EQ(a.r_count(), 1);

}

TEST(TestSharedPtr, NullptrConstructor) {

    SharedPtr<int> a(nullptr);

    EXPECT_EQ(a.get(), nullptr);
    EXPECT_EQ(a.r_count(), 0);

}

TEST(TestSharedPtr, CopyConstructor) {

    SharedPtr<int> a(new int(10));
    SharedPtr<int> b(a);

    EXPECT_EQ(*a, 10);
    EXPECT_EQ(*b, 10);

    EXPECT_EQ(a.r_count(), 2);
    EXPECT_EQ(b.r_count(), 2);

}

TEST(TestSharedPtr, MoveConstructor) {

    SharedPtr<int> a(new int(10));
    SharedPtr<int> b(std::move(a));

    EXPECT_EQ(a.get(), nullptr);
    EXPECT_EQ(a.r_count(), 0);

    EXPECT_EQ(*b, 10);
    EXPECT_EQ(b.r_count(), 1);

}

TEST(TestSharedPtrArray, Constructor) {

    SharedPtr<int[]> arr(new int[3]{0, 1, 2});

    EXPECT_EQ(arr[0], 0);
    EXPECT_EQ(arr[1], 1);
    EXPECT_EQ(arr[2], 2);

}

TEST(TestSharedPtrArray, NullptrConstructor) {

    SharedPtr<int[]> arr(nullptr);

    EXPECT_EQ(arr.get(), nullptr);
    EXPECT_EQ(arr.r_count(), 0);

}

TEST(TestSharedPtrArray, CopyConstructor) {

    SharedPtr<int[]> arr1(new int[3]{0, 1, 2});
    SharedPtr<int[]> arr2(arr1);

    EXPECT_EQ(arr2[0], 0);
    EXPECT_EQ(arr2[1], 1);
    EXPECT_EQ(arr2[2], 2);

    EXPECT_EQ(arr1.r_count(), 2);
    EXPECT_EQ(arr2.r_count(), 2);

}

TEST(TestSharedPtrArray, MoveConstructor) {

    SharedPtr<int[]> arr1(new int[3]{0, 1, 2});
    SharedPtr<int[]> arr2(std::move(arr1));

    EXPECT_EQ(arr1.get(), nullptr);
    EXPECT_EQ(arr1.r_count(), 0);

    EXPECT_EQ(arr2[0], 0);
    EXPECT_EQ(arr2[1], 1);
    EXPECT_EQ(arr2[2], 2);

}

TEST(TestSharedPtr, ResetNewObject) {

    SharedPtr<int> a(new int(10));

    a.reset(new int(20));

    EXPECT_EQ(*a, 20);
    EXPECT_EQ(a.r_count(), 1);

}

TEST(TestSharedPtrArray, ResetNewArray) {

    SharedPtr<int[]> arr(new int[3]{1, 2, 3});

    arr.reset(new int[1]{11});

    EXPECT_EQ(arr[0], 11);
    EXPECT_EQ(arr.r_count(), 1);

}

TEST(TestSharedPtr, ResetSamePointer) {

    SharedPtr<int> a(new int(20));

    int* ptr = a.get();

    a.reset(ptr);

    EXPECT_EQ(*a, 20);
    EXPECT_EQ(a.r_count(), 1);

}

TEST(TestSharedPtrArray, ResetSamePointer) {

    SharedPtr<int[]> arr(new int[2]{10, 20});

    int* ptr = arr.get();

    arr.reset(ptr);

    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
    EXPECT_EQ(arr.r_count(), 1);

}

TEST(TestSharedPtr, ResetNullptr) {

    SharedPtr<int> a(new int(10));

    a.reset(nullptr);

    EXPECT_EQ(a.get(), nullptr);
    EXPECT_EQ(a.r_count(), 0);

}

TEST(TestSharedPtrArray, ResetNullptr) {

    SharedPtr<int[]> arr(new int[3]{1, 2, 3});

    arr.reset(nullptr);

    EXPECT_EQ(arr.get(), nullptr);
    EXPECT_EQ(arr.r_count(), 0);

}

TEST(TestSharedPtr, ResetSharedObject) {

    SharedPtr<int> a(new int(10));
    SharedPtr<int> b(a);

    EXPECT_EQ(a.r_count(), 2);
    EXPECT_EQ(b.r_count(), 2);

    a.reset();

    EXPECT_EQ(a.get(), nullptr);
    EXPECT_EQ(a.r_count(), 0);

    EXPECT_EQ(*b, 10);
    EXPECT_EQ(b.r_count(), 1);

}

TEST(TestSharedPtrArray, ResetSharedArray) {

    SharedPtr<int[]> arr1(new int[3]{1, 2, 3});
    SharedPtr<int[]> arr2(arr1);

    EXPECT_EQ(arr1.r_count(), 2);
    EXPECT_EQ(arr2.r_count(), 2);

    arr1.reset();

    EXPECT_EQ(arr1.get(), nullptr);
    EXPECT_EQ(arr1.r_count(), 0);

    EXPECT_EQ(arr2[0], 1);
    EXPECT_EQ(arr2[1], 2);
    EXPECT_EQ(arr2[2], 3);
    EXPECT_EQ(arr2.r_count(), 1);

}

TEST(TestSharedPtr, CopyAssignment) {

    SharedPtr<int> a(new int(5));
    SharedPtr<int> b;

    b = a;

    EXPECT_EQ(*a, 5);
    EXPECT_EQ(*b, 5);

    EXPECT_EQ(a.r_count(), 2);
    EXPECT_EQ(b.r_count(), 2);

}

TEST(TestSharedPtr, MoveAssignment) {

    SharedPtr<int> a(new int(5));
    SharedPtr<int> b(a);
    SharedPtr<int> c;

    c = std::move(b);

    EXPECT_EQ(b.get(), nullptr);
    EXPECT_EQ(b.r_count(), 0);

    EXPECT_EQ(*a, 5);
    EXPECT_EQ(*c, 5);

    EXPECT_EQ(a.r_count(), 2);
    EXPECT_EQ(c.r_count(), 2);

}

TEST(TestSharedPtr, SelfAssignment) {

    SharedPtr<int> a(new int(5));

    a = a;

    EXPECT_EQ(*a, 5);
    EXPECT_EQ(a.r_count(), 1);

}

TEST(TestSharedPtr, DereferenceOperator) {

    SharedPtr<TestObj> a(new TestObj(10));

    EXPECT_EQ((*a).get(), 10);

}

TEST(TestSharedPtr, ArrowOperator) {

    SharedPtr<TestObj> a(new TestObj(10));

    EXPECT_EQ(a->get(), 10);

}

TEST(TestSharedPtrArray, IndexOperator) {

    SharedPtr<int[]> arr(new int[3]{1, 2, 3});

    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 3);

}

TEST(TestSharedPtrArray, CopyAssignment) {

    SharedPtr<int[]> arr1(new int[3]{1, 2, 3});
    SharedPtr<int[]> arr2;

    arr2 = arr1;

    EXPECT_EQ(arr2[0], 1);
    EXPECT_EQ(arr2[1], 2);
    EXPECT_EQ(arr2[2], 3);

    EXPECT_EQ(arr1.r_count(), 2);
    EXPECT_EQ(arr2.r_count(), 2);

}

TEST(TestSharedPtrArray, SharedData) {

    SharedPtr<int[]> arr1(new int[3]{1, 2, 3});
    SharedPtr<int[]> arr2(arr1);

    arr2[1] = 10;

    EXPECT_EQ(arr1[1], 10);
    EXPECT_EQ(arr2[1], 10);

}

TEST(TestSharedPtrArray, MoveAssignment) {

    SharedPtr<int[]> arr1(new int[3]{1, 2, 3});
    SharedPtr<int[]> arr2(arr1);
    SharedPtr<int[]> arr3;

    arr3 = std::move(arr2);

    EXPECT_EQ(arr2.get(), nullptr);
    EXPECT_EQ(arr2.r_count(), 0);

    EXPECT_EQ(arr3[0], 1);
    EXPECT_EQ(arr3[1], 2);
    EXPECT_EQ(arr3[2], 3);

    EXPECT_EQ(arr1.r_count(), 2);
    EXPECT_EQ(arr3.r_count(), 2);

}

TEST(TestSharedPtrArray, SelfAssignment) {

    SharedPtr<int[]> arr(new int[3]{1, 2, 3});

    arr = arr;

    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 3);

    EXPECT_EQ(arr.r_count(), 1);

}

TEST(TestSharedPtrArray, ConstIndexOperator) {

    SharedPtr<int[]> arr(new int[3]{1, 2, 3});

    const SharedPtr<int[]>& const_arr = arr;

    EXPECT_EQ(const_arr[0], 1);
    EXPECT_EQ(const_arr[1], 2);
    EXPECT_EQ(const_arr[2], 3);

}

TEST(TestSharedPtr, MakeShared) {

    auto a = makeShared<int>(10);

    EXPECT_EQ(*a, 10);
    EXPECT_EQ(a.r_count(), 1);

}

TEST(TestSharedPtrArray, MakeSharedArray) {

    auto arr = makeSharedArray<int>(3);

    arr[0] = 0;
    arr[1] = 1;
    arr[2] = 2;

    EXPECT_EQ(arr[0], 0);
    EXPECT_EQ(arr[1], 1);
    EXPECT_EQ(arr[2], 2);

    EXPECT_EQ(arr.r_count(), 1);

}
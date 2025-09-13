#include <iostream>
#include <string>
#include "gtest/gtest.h"

// Const expr 使用时的注意事项
// 1. const变量可以在运行时初始化
// 2. constexpr 必须在编译期初始化
// 3. constexpr 肯定是const, const不一定是constexpr
// 4. const变量来指定变量不可以更改
// 5. constexpr变量用来指定变量需要在编译期计算值

template <typename T, std::size_t N> 
std::size_t get_size(T (&) [N]) {
    return N;
}

GTEST_TEST(ConstExprTests, ConstAndConstExprTheSame) {
    int constexpr i = 10;
    int arr[i];
    std::cout << get_size(arr) << std::endl;
    ASSERT_EQ(get_size(arr), 10);

    int const j = 5;
    int arr1[j];
    ASSERT_EQ(get_size(arr1), 5);
}

int constexpr get_number() {
    return 42;
}

GTEST_TEST(ConstExprTests, ConstExprAssign) {
    int constexpr i = get_number();
    int arr[i];
    ASSERT_EQ(get_size(arr), 42);

    int const j = get_number();
    int arr1[j];
    ASSERT_EQ(get_size(arr1), 42);
}

// C++ 11 constexpr function 只允许一行, C++ 14可以多行
int constexpr add(int x, int y) {
    return x + y;
}

GTEST_TEST(ConstExprTests, ConstExprLineFunc) {
    int constexpr sum = add(3, 5);
    ASSERT_EQ(sum, 8);
}

GTEST_TEST(ConstExprTests, InvokeWithNonConstParams) {
    // 必须是const的才能加入add函数，否则编译会崩
    int const x = 10;
    int constexpr sum = add(x, 5);
    ASSERT_EQ(sum, 15);
}

// Works in C++ 14 and above
int constexpr max(int x, int y) {
    if(x > y) {
        return x;
    }
    return y;
}


GTEST_TEST(ConstExprTests, ConstExprMultiLineFunc) {
    int constexpr max_res = max(3, 5);
    ASSERT_EQ(max_res, 5);
}
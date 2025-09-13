#include <iostream>
#include <string>
#include <cassert>
#include <initializer_list>
#include "gtest/gtest.h"

/**
 * std::initializer_list注意事项:
 * 1. 轻量级的数组对象
 * 2. 自动从花括号列表创建
 * 使用范围: auto/ range-based-for-loop/ 构造函数/ 函数参数
 * 3. 不是真正的容器，但是有类似容器的行为
 * 4. 可以使用迭代器访问元素
 * 5. 头文件是<initializer_list> 
*/
template <typename IT, typename Ele>
void ASSERT_LIST_EQ(IT begin, IT end, std::initializer_list<Ele> const& expects) {
    for(auto actual = begin, exp=std::begin(expects); actual!=end && exp!=std::end(expects); ++actual, ++exp) {
        ASSERT_EQ(*actual, *exp);
    }
}

GTEST_TEST(StdInitialList, BasicUsage) {
    int x{0};
    ASSERT_EQ(x, 0);
    float y{3.1f};
    ASSERT_EQ(y, 3.1f);
    int arr[5]{3, 1, 3, 8, 2};
    ASSERT_LIST_EQ(std::begin(arr), std::end(arr), {3, 1, 3, 8, 2});
    std::string s{"Hello C++"};
    ASSERT_EQ(s, "Hello C++");
    std::initializer_list<int> data {1, 2, 3, 4};
    ASSERT_LIST_EQ(data.begin(), data.end(), {1, 2, 3, 4});
    auto values = {1, 2, 3, 4};
    ASSERT_LIST_EQ(values.begin(), values.end(), {1, 2, 3, 4});
}


template <typename T, std::size_t  N=10>
class Bag {
    T arr[N];
    int m_size{};

public:
    Bag(std::initializer_list<T> const& values) {
        assert(values.size() < N);
        for(auto it=values.begin(); it!=values.end(); ++it) {
            add(*it);
        }
    }
    void add(T value) {
        assert(m_size < N);
        arr[m_size++] = value;
    }

    T* begin() {
        return &arr[0];
    }

    T* end() {
        return &arr[m_size];
    }

    T* operator++() {
        assert(m_size < N);
        return &arr[++m_size];
    }

    void remove() {
        --m_size;
    }

    T& operator[] (std::size_t index) {
        return arr[index];
    } 
    int get_size() const {
        return m_size;
    }
 
};

GTEST_TEST(StdInitialList, TestBag) {
    Bag<int> b{3, 1, 8};
    for(auto ele: b) {
        std::cout << ele << std::endl;
    }

    ASSERT_LIST_EQ(b.begin(), b.end(), {3, 1, 8});

    b.add(8);
    b.add(3);
    for(auto ele: b) {
        std::cout << ele << std::endl;
    }

    ASSERT_LIST_EQ(b.begin(), b.end(), {3, 1, 8, 8, 3});
}


void print(std::initializer_list<int> const& values) {
    for(auto x: values) {
        std::cout << x << " ";
    }
    std::cout << "\n";
}


GTEST_TEST(StdInitialList, TestPrint) {
    print({1, 2, 3, 4});
    for(auto x: {1, 2, 3, 4}) {
        std::cout << x << " ";
    }
    std::cout << "\n";
}

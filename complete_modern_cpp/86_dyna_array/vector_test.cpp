#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "gtest/gtest.h"

template <typename IT, typename Ele>
void ASSERT_LIST_EQ(IT begin, IT end, std::initializer_list<Ele> const& expects) {
    for(auto actual = begin, exp=std::begin(expects); actual!=end && exp!=std::end(expects); ++actual, ++exp) {
        ASSERT_EQ(*actual, *exp);
    }
}


GTEST_TEST(StdVector, DynamicArray) {
    std::size_t size = 10;
    std::shared_ptr<int[]> arr {new int[size], std::default_delete<int[]>()};
    for(std::size_t i=0; i<size; ++i) {
        arr[i] = i*10;
    }

    for(std::size_t i=0; i<size; ++i) {
        std::cout << arr[i] << ",";
    }
    std::cout << std::endl;
    ASSERT_LIST_EQ(arr.get(), arr.get() + size,  {0,10,20,30,40,50,60,70,80,90});
}

GTEST_TEST(StdVector, BaiscUsage) {
    std::vector<int> data{1, 2, 3};
    for(std::size_t i=0; i<5; ++i) {
        data.push_back(i* 10);
    }
    for(std::size_t i=0; i<data.size(); ++i) {
        std::cout << data[i] << ", ";
    }
    std::cout << std::endl;
    ASSERT_LIST_EQ(data.begin(), data.end(), {1, 2, 3, 0, 10, 20, 30, 40});
}

GTEST_TEST(StdVector, RangeBasedForLoop) {
    std::vector<int> data{1, 2, 3};
    for(auto const& x: data) {
        std::cout << x << ",";
    }
    std::cout << std::endl;
    ASSERT_LIST_EQ(data.begin(), data.end(), {1, 2, 3});
}

GTEST_TEST(StdVector,  IteraterUsage) { 
    std::vector<int> data{1, 2, 3};
    for(auto it=data.begin(); it!=data.end(); ++it) {
        std::cout << *it << ",";
    }
    std::cout << std::endl;
    ASSERT_LIST_EQ(data.begin(), data.end(), {1, 2, 3});
}

GTEST_TEST(StdVector,  IteraterRemoveFirst) { 
    std::vector<int> data{1, 2, 3};
    data.erase(data.begin());
    ASSERT_LIST_EQ(data.begin(), data.end(), {2, 3});
}


GTEST_TEST(StdVector,  IteratorInsertThe2nd) { 
    std::vector<int> data{1, 2, 3};
    data.insert(data.begin() + 2, 500);
    ASSERT_LIST_EQ(data.begin(), data.end(), {1, 2, 500, 3});
}


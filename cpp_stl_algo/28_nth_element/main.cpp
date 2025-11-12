#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

#include <iostream>
#include <vector>
#include <map>
#include <random>
#include <string>
#include <algorithm>


std::vector<int> v {1, 5, 4, 2, 9, 7, 3, 8, 2};

template <typename T>
void print_vector(const std::vector<T>& v) {
    std::for_each(std::begin(v), std::end(v), [](const T& elem) {
        std::cout << elem << " ";
    });
    std::cout << std::endl;
}

TEST_CASE("Nth element") {
    // 1. nth_element的定义：第n个元素，不管元素值是多少，
    // 左边的数字将会小于这个元素，右边的数字将会大于这个元素。
    // 左右的数字都是无序的。
    int i = *(std::begin(v) + 4);
    std::cout << "Before nth_element: ";
    print_vector(v);
    std::cout << "The 5th element is: " << i << std::endl;
    nth_element(std::begin(v), std::begin(v) + 4, std::end(v));
    i = *(std::begin(v) + 4);
    std::cout << "After nth_element: ";
    print_vector(v);
    std::cout << "The 5th element is: " << i << std::endl;
}

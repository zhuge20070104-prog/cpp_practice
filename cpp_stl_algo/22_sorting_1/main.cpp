#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>


std::vector<int> v {4, 1, 0, 1, -2, 3, 7, -6, 2, 0, 0, -9, 9};

template <typename T>
void print_vector(const std::vector<T>& v) {
    std::for_each(std::begin(v), std::end(v), [](auto const& elem) {
        std::cout << elem << " ";
    });
    std::cout << std::endl;
}

TEST_CASE("Sorting a vector") {
    std::sort(std::begin(v), std::end(v));
    std::cout << "After sorting: ";
    print_vector(v);

    std::sort(std::begin(v), std::end(v), [] (int elem1, int elem2) {
        return elem1 > elem2;
    });

    std::cout << "After sorting in descending order: ";
    print_vector(v);

    std::sort(std::begin(v), std::end(v), [](int elem1, int elem2) {
        return abs(elem1) > abs(elem2);
    });

    std::cout << "After sorting by absolute value in descending order: ";
    print_vector(v);
}

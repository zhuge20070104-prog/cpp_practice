#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

#include <iostream>
#include <vector>
#include <map>
#include <random>
#include <string>
#include <algorithm>


std::vector<int> v {4, 1, 0, 1, -2, 3, 7, -6, 2, 0, 0, -9, 9};

template <typename T>
void print_vector(const std::vector<T>& v) {
    std::for_each(std::begin(v), std::end(v), [](const T& elem) {
        std::cout << elem << " ";
    });
    std::cout << std::endl;
}

TEST_CASE("Partial sorting") {
    std::vector<int> v2(v);
    std::cout << "Before shuffling: ";
    print_vector(v2);
    std::random_device rd;
    std::mt19937 generator(rd());
    std::shuffle(std::begin(v2), std::end(v2), generator);
    std::cout << "After shuffling: ";
    print_vector(v2);
    
    std::partial_sort(std::begin(v2), std::find(std::begin(v2), std::end(v2), 4), std::end(v2));
    std::cout << "After partial sorting: ";
    print_vector(v2);

    std::cout << "Things not sorted: ";
    auto break_point_it = std::is_sorted_until(std::begin(v2), std::end(v2));
    while(break_point_it != std::end(v2)) {
        std::cout << *break_point_it << " ";
        ++break_point_it;
    }
    std::cout << std::endl;

    std::vector<int> v3(3);
    std::partial_sort_copy(std::begin(v), std::end(v), std::begin(v3), std::end(v3));
    std::cout << "After partial sort copy: ";
    print_vector(v3);
}

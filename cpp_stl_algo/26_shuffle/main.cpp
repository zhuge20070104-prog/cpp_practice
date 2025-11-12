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

TEST_CASE("Shuffle") {
    std::cout << "Before shuffling: ";
    print_vector(v);
    std::random_device rd;
    std::mt19937 generator(rd());
    std::shuffle(std::begin(v), std::end(v), generator);

    std::cout << "After shuffling: ";
    print_vector(v);
}

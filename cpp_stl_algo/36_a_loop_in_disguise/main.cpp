#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

#include <iostream>
#include <vector>
#include <map>
#include <random>
#include <string>
#include <algorithm>


template <typename T>
void print_vector(const std::vector<T>& v) {
    std::for_each(std::begin(v), std::end(v), [](const T& elem) {
        std::cout << elem << " ";
    });
    std::cout << std::endl;
}

std::vector<int> a {1, 2, 3, 4, 5};

TEST_CASE("Modify a vector in three different ways") {
    std::vector<int> b(a);

    for(auto it = std::begin(b); it != std::end(b); ++it) {
        *it = 0;
    }

    print_vector(b);

    for(auto& i: b) {
        i = 1;
    }
    print_vector(b);

    std::for_each(std::begin(b), std::end(b), [](int& elem) {
        elem = 2;
    });
    print_vector(b);
}

TEST_CASE("Only modify the elements after 3") {
    std::vector<int> b(a);

    auto first_three = std::find(std::begin(b), std::end(b), 3);
    std::for_each(first_three, std::end(b), [](int& elem) {
        elem = 0;
    });

    print_vector(b);
}

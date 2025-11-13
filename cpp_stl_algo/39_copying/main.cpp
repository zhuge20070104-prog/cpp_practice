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

std::vector<int> source {3, 6, 1, 0, -2, 5};

TEST_CASE("Copy elements") {
    std::vector<int> v2(source.size());
    std::cout << "Copy using std::copy: " << std::endl;
    std::copy(std::begin(source), std::end(source), std::begin(v2));
    print_vector(v2);
    
    std::cout << "Copy using copy constructor: " << std::endl;
    auto v3(source);
    print_vector(v3);

    std::cout << "Copy partial set of elements: " << std::endl;

    auto position = std::find(std::begin(source), std::end(source), 1);
    std::vector<int> v4(source.size());
    std::copy(std::begin(source), position, std::begin(v4));
    print_vector(v4);
}


TEST_CASE("Self copy") {
    std::cout << "Self copy: " << std::endl;
    auto position = std::find(std::begin(source), std::end(source), 1);
    std::copy(std::begin(source), position + 1, position + 1);
    print_vector(source);


    std::cout << "Self copy with element outside the range: " << std::endl;
    std::copy_backward(std::begin(source), std::end(source) - 1, std::end(source));
    print_vector(source);
}
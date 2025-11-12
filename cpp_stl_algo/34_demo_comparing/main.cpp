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

TEST_CASE("Std equal not equal") {
    std::cout << "Std equal not equal" << std::endl;
    std::vector<int> a {1, 2, 3, 4, 5};
    std::vector<int> b {1, 2, 0, 4};

    bool same = (a.size() == b.size());

    for(std::size_t i=0; i<a.size() && same; ++i) {
        if(a[i] != b[i]) {
            same = false;
        }
    }

    std::cout << "Same by hand: " << same << std::endl;
    same = std::equal(std::begin(a), std::end(a), std::begin(b), std::end(b));
    std::cout << "Same by std::equal: " << same << std::endl;
}


TEST_CASE("Std equal equals") {
    std::cout << "Std equal equals" << std::endl;
    std::vector<int> a {1, 2, 3, 4, 5};
    std::vector<int> b {1, 2, 3, 4, 5};
    
    bool same = (a.size() == b.size());
    for(std::size_t i=0; i<a.size() && same; ++i) {
        if(a[i] != b[i]) {
            same = false;
        }
    }

    std::cout << "Same by hand: " << same << std::endl;

    same = std::equal(std::begin(a), std::end(a), std::begin(b), std::end(b));
    std::cout << "Same by std::equal: " << same << std::endl;
}

TEST_CASE("Std mismatch") {
    std::cout << "Std mismatch" << std::endl;
    std::vector<int> a {1, 2, 3, 4, 5};
    std::vector<int> b {1, 2, 0, 4};

    auto result = std::mismatch(std::begin(a), std::end(a), std::begin(b));
    int avalue = *result.first;
    int bvalue = *result.second;
    auto distance = result.first - std::begin(a);
    std::cout << "First mismatch value, avalue: " << avalue << ", bvalue: " << bvalue << '\n';
    std::cout << "First mismatch distance: " << distance << '\n';
}
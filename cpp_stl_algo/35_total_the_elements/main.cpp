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

TEST_CASE("Std accumulate integer") {
    std::vector<int> a {1, 2, 3, 4, 5};

    int total = 0;
    for(int i: a) {
        total += i;
    }
    std::cout << "Total by hand: " << total << std::endl;
    
    total = std::accumulate(std::begin(a), std::end(a), 0);
    std::cout << "Total by std::accumulate: " << total << std::endl;

    total = std::accumulate(std::begin(a), std::end(a), 0, [](int total, int i) {
        if(i % 2 == 0) {
            return total += i;
        }
        return total;
    });
    std::cout << "std::accumulate even numbers: " << total << std::endl;

    total = std::accumulate(std::begin(a), std::end(a), 1, [](int total, int i) {
        return total * i;
    });
    std::cout << "std::accumulate product of all numbers: " << total << std::endl;
}


TEST_CASE("Std accumulate string") {
    std::vector<std::string> words {"one", "two", "three"};

    auto all_words = std::accumulate(std::begin(words), std::end(words), std::string(""));
    int length = all_words.size();
    std::cout << "All words: " << all_words << std::endl;
    std::cout << "Length of all words: " << length << std::endl;

    all_words = std::accumulate(std::begin(words), std::end(words), std::string("Words: "), [](const std::string& total, std::string& word) {
        return total + " " + word;
    });
    std::cout << "All words: " << all_words << std::endl;

    std::vector<int> a {1, 2, 3, 4, 5};
    std::string num_str = std::accumulate(std::begin(a), std::end(a), std::string("The numbers are: "), [](const std::string& total, int i) {
        return total + " " + std::to_string(i);
    });

    std::cout << "Numbers: " << num_str << std::endl;
}
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



TEST_CASE("Reversing and swapping") {
  std::vector<int> v {1, 2, 3, 4, 5};

  std::string sentence = "Hello, world!";
  std::reverse(std::begin(sentence), std::end(sentence));
  std::cout << "Reversed sentence: " << sentence << std::endl;

  std::iter_swap(std::begin(v), std::end(v) - 1);
  std::cout << "Swapped first and last element: " << std::endl;
  print_vector(v);

  std::string dest = "";
  std::reverse_copy(std::begin(sentence), std::end(sentence), std::back_inserter(dest));
  std::cout << "Reversed copy of sentence: " << dest << std::endl;
}

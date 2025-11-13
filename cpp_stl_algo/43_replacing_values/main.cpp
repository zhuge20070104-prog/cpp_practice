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



TEST_CASE("Replacing values") {
  std::vector<int> v6(10);
  std::iota(std::begin(v6), std::end(v6), 1);
  int index = 1;
  std::cout << "Original vector: " << std::endl;
  std::generate_n(std::begin(v6), 7, [&index]() {
    return index *= 2;
  });
  print_vector(v6);

  std::replace(std::begin(v6), std::end(v6), 2, 7);
  std::cout << "std::replace all 2s with 7s: " << std::endl;
  print_vector(v6);

  std::replace_if(std::begin(v6), std::end(v6), [](int elem) {
    return elem < 16;
  }, 7);
  std::cout << "std::replace_if all elements less than 16 with 7s: " << std::endl;
  print_vector(v6);
}

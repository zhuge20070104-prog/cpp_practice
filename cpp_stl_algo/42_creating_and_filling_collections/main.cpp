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



TEST_CASE("Fill and generate") {
  std::vector<int> v6(10);
  std::cout << "std::fill ten 1s: " << std::endl;
  std::fill(std::begin(v6), std::end(v6), 1);
  print_vector(v6);

  std::fill_n(std::begin(v6), 6, 2);
  std::cout << "std::fill_n six 2s: " << std::endl;
  print_vector(v6);

  std::iota(std::begin(v6), std::end(v6), 1);
  std::cout << "std::iota ten numbers from 1 to 10: " << std::endl;
  print_vector(v6);

  int index = 10;
  std::cout << "std::generate ten numbers from 10 to 1: " << std::endl;
  std::generate(std::begin(v6), std::end(v6), [&index]() {
    return --index;
  });
  print_vector(v6);

  index = 1;
  std::cout << "std::generate_n seven numbers from 2 to 128: " << std::endl;
  std::generate_n(std::begin(v6), 7, [&index]() {
    return index *= 2;
  });
  print_vector(v6);
}

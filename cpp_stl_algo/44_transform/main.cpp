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



TEST_CASE("transform") {
  std::vector<int> source(10);
  int index = 10;
  std::generate(std::begin(source), std::end(source), [&index]() {
    return index--;
  });

  std::cout << "Original vector: " << std::endl;
  print_vector(source);

  std::transform(std::begin(source), std::end(source), std::begin(source), [](int elem) {
    return elem * 2;
  });

  std::cout << "std::transform all elements by 2: " << std::endl;
  print_vector(source);

  std::vector<int> v6(10);
  std::transform(std::begin(source), std::end(source) - 1, std::begin(source) + 1, std::begin(v6), [](int elem1, int elem2) {
    return elem1 - elem2;
  });

  std::cout << "std::transform reduce the neighboring elements: " << std::endl;
  print_vector(v6);

  std::iota(std::begin(v6), std::end(v6), 1);
  std::iota(std::begin(source), std::end(source), 2);
  std::vector<int> v7(10);
  std::transform(std::begin(v6), std::end(v6), std::begin(source), std::begin(v7), [](int elem1, int elem2) {
    return elem1 + elem2;
  });

  std::cout << "std::transform add the elements of two vectors: " << std::endl;
  print_vector(v7);
}

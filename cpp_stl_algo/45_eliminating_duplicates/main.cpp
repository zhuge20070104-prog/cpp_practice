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



TEST_CASE("Unique") {
  //   sort, unique，直接在原集合上操作，unique依赖于sort
  // 需要先sort，再unique
  std::vector<int> v {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
  std::vector<int> v2(v);
  std::cout << "Original vector: " << std::endl;
  print_vector(v);
  std::unique(std::begin(v), std::end(v));
  std::cout << "Unique without order: " << std::endl;
  print_vector(v);

  std::sort(std::begin(v), std::end(v));
  std::cout << "After sorting: " << std::endl;
  print_vector(v);
  v.erase(std::unique(std::begin(v), std::end(v)), std::end(v));
  std::cout << "Unique with order: " << std::endl;
  print_vector(v);

  std::vector<int> v8(10);
  std::sort(std::begin(v2), std::end(v2));
  std::unique_copy(std::begin(v2), std::end(v2), std::begin(v8));
  std::cout << "Unique copy v2 and v8: " << std::endl;
  print_vector(v2);
  print_vector(v8);
}

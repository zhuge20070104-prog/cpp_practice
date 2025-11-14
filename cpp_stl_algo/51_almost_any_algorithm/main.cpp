#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

#include <iostream>
#include <vector>
#include <map>
#include <random>
#include <string>
#include <algorithm>
#include <deque>


template <typename Container>
void print_container(const Container& v) {
    using T = typename Container::value_type;
    std::for_each(std::begin(v), std::end(v), [](const T& elem) {
        std::cout << elem << " ";
    });
    std::cout << std::endl;
}



TEST_CASE("Iterators in any algorithm") {
  std::vector<int> v1(10);
  std::iota(std::begin(v1), std::end(v1), 1);
  std::cout << "v1: ";
  print_container(v1);


  std::vector<int> v2;
  std::transform(std::begin(v1), std::end(v1), std::back_inserter(v2),
    [](int elem) {
      return elem * 2;
    });
  std::cout << "v2: ";
  print_container(v2);

  std::vector<int> v3 {3, 6, 1, 0, -2, 5};
  std::vector<int> v5;
  std::copy_if(std::begin(v3), std::end(v3), std::back_inserter(v5),
    [](int elem) {
      return elem % 2 == 0;
    });

  std::cout << "v5: ";
  print_container(v5);


  v3[3] = -2;
  std::vector<int> v6;

  std::unique_copy(std::begin(v3), std::end(v3), std::back_inserter(v6));
  std::cout << "v6: ";
  print_container(v6);
}

#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

#include <iostream>
#include <vector>
#include <array>
#include <map>
#include <random>
#include <string>
#include <algorithm>


template <typename Container>
void print_container(const Container& v) {
    using T = typename Container::value_type;
    std::for_each(std::begin(v), std::end(v), [](const T& elem) {
        std::cout << elem << " ";
    });
    std::cout << std::endl;
}


TEST_CASE("Iterator to const element") {
  std::array<const int, 5> ca {3, 1, 6, 0, 2};
  print_container(ca);
  auto it = std::begin(ca);
  it++;
  // *it = 7; not work here, since it is a const element
  int i = *it;
  std::cout << "i: " << i << std::endl;
}

TEST_CASE("Vector const iterator") {
  std::vector<int> v2 {3, 1, 6, 0, 2};
  print_container(v2);
  auto it = std::begin(v2);
  it++;
  *it = 7;
  int i = *it;
  std::cout << "i: " << i << std::endl;

  print_container(v2);

  auto cit = std::cbegin(v2);
  cit++;
  // *cit = 8; const iterator cannot be modified
  int j = *cit;
  std::cout << "j: " << j << std::endl;
  print_container(v2);
}
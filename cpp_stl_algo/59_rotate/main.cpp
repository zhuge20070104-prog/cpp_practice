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


TEST_CASE("Rotate") {
  std::vector<int> tasks(6);
  std::iota(std::begin(tasks), std::end(tasks), 1);
  
  print_container(tasks);
  auto two = std::find(std::begin(tasks), std::end(tasks), 2);
  auto four = std::find(std::begin(tasks), std::end(tasks), 4);
  std::rotate(two, four, four + 1);
  print_container(tasks);
  
  std::vector<int> v_copy(tasks);
  auto two_copy = std::find(std::begin(v_copy), std::end(v_copy), 2);
  std::rotate(std::begin(v_copy), two_copy, two_copy + 1);
  print_container(v_copy);
}
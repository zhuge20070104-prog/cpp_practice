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



TEST_CASE("Reverse iterators") {
  std::vector<int> v1(10);
  std::iota(std::begin(v1), std::end(v1), 1);
  std::vector<int> v2;
  std::copy(std::rbegin(v1), std::rend(v1), std::back_inserter(v2));
  std::cout << "v2: ";
  print_container(v2);

  // 1, 2, 3, 4, 5, 2, 7, 8, 9, 10
  v1[5] = 2;
  auto two = std::find(std::begin(v1), std::end(v1), 2);
  auto distance = two - std::begin(v1);
  two++;
  std::cout << "Distance: " << distance << std::endl;
  std::cout << "Two: " << *two << std::endl;

  auto rtwo = std::find(std::rbegin(v1), std::rend(v1), 2);
  distance = rtwo - std::rbegin(v1);
  std::cout << "Distance: " << distance << std::endl;
  rtwo++;
  std::cout << "Rtwo: " << *rtwo << std::endl;
}

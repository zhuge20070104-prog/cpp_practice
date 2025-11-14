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



TEST_CASE("Fill collection with known size") {
  std::vector<int> v(10);
  std::fill(std::begin(v), std::end(v), 1);
  std::cout << "Fill vector with 1s: " << std::endl;
  print_container(v);

  std::fill_n(std::begin(v), 6, 2);
  std::cout << "Fill first 6 elements with 2s: " << std::endl;
  print_container(v);

  std::iota(std::begin(v), std::end(v), 1);
  std::cout << "Fill vector with 1s to 10: " << std::endl;
  print_container(v); 
}


TEST_CASE("Fill collection with unknown size") {
  std::vector<int> v2;
  std::fill_n(std::back_inserter(v2), 6, 2);
  int n = 0;
  std::generate_n(std::back_inserter(v2), 10, [n]() mutable {
    return n++;
  });

  std::cout << "Fill vector with 2s and 1s to 10: " << std::endl;
  print_container(v2);

  std::deque<int> q3;
  std::fill_n(std::front_inserter(q3), 6, 2);
  std::generate_n(std::front_inserter(q3), 10, [n=0]() mutable {
    return n++;
  });

  std::cout << "Fill deque with 2s and 1s to 10: " << std::endl;
  print_container(q3);
}

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


TEST_CASE("Swapping") {
  std::vector<int> evens {2, 4, 6, 8, 10};
  std::vector<int> odds {1, 3, 5, 7, 9};
  std::cout << "Before swapping:" << std::endl;
  std::cout << "Evens: ";
  print_container(evens);
  std::cout << "Odds: ";
  print_container(odds);


  auto v1 = evens;
  std::swap(v1[0], v1[1]);
  std::cout << "After swapping the first two elements:" << std::endl;
  std::cout << "v1: ";
  print_container(v1);
  std::iter_swap(std::begin(v1), std::begin(v1) + 1);
  std::cout << "After iter_swap:" << std::endl;
  std::cout << "v1: ";
  print_container(v1);

  auto v2 = odds;

  std::swap(v1[0], v2[0]);
  std::cout << "After swapping the first elements:" << std::endl;
  std::cout << "v1: ";
  print_container(v1);
  std::cout << "v2: ";
  print_container(v2);

  std::iter_swap(std::begin(v1), std::find(std::begin(v2), std::end(v2), 5));
  std::cout << "After iter_swap:" << std::endl;
  std::cout << "v1: ";
  print_container(v1);
  std::cout << "v2: ";
  print_container(v2);


  v1 = evens;
  v2 = odds;

  std::swap_ranges(std::begin(v1), std::find(std::begin(v1), std::end(v1), 6), std::begin(v2));
  std::cout << "After swap_ranges:" << std::endl;
  std::cout << "v1: ";
  print_container(v1);
  std::cout << "v2: ";
  print_container(v2);
  
}
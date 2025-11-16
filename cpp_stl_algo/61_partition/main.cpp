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


TEST_CASE("Rotate and partition") {
  std::vector<int> numbers(8);
  std::iota(std::begin(numbers), std::end(numbers), 1);
  std::cout << "Original numbers: ";
  print_container(numbers);

  auto selected = std::stable_partition(std::begin(numbers), std::end(numbers), [](int elem) {
    return elem % 2 != 0;
  });

  std::cout << "After partition: ";
  print_container(numbers);

  std::cout << "Selected numbers: ";
  std::cout << "Selected number: " << *selected << std::endl;

  std::rotate(std::begin(numbers), selected, selected + 1);
  std::cout << "After rotate: ";
  print_container(numbers);
}
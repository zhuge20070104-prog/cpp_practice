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



TEST_CASE("Iterator arithmatic") {
  std::vector<int> v1(10);
  std::iota(std::begin(v1), std::end(v1), 1);
  v1[5] = 2;
  print_container(v1);
  auto two = std::find(std::begin(v1), std::end(v1), 2);
  auto distance = two - std::begin(v1);
  two++;
  std::cout << "Distance: " << distance << std::endl;
  std::cout << "Two after increment: " << *two << std::endl;

  auto rtwo = std::find(std::rbegin(v1), std::rend(v1), 2);
  auto rdistance = rtwo - std::rbegin(v1);
  rtwo++;
  std::cout << "Rdistance: " << rdistance << std::endl;
  std::cout << "Rtwo after increment: " << *rtwo << std::endl;
}

TEST_CASE("Iterator arithmetic firsthalf") {
  std::vector<int> v1(10);
  std::iota(std::begin(v1), std::end(v1), 1);
  v1[5] = 2;
  print_container(v1);

  auto three = std::find(std::begin(v1), std::end(v1), 3);
  bool three_in_firsthalf = ((three - std::begin(v1)) < (std::end(v1) - three));
  std::cout << "Three in first half: " << std::boolalpha << three_in_firsthalf << std::endl;

  auto nine = std::find(std::begin(v1), std::end(v1), 9);
  bool nine_in_firsthalf = ((nine - std::begin(v1)) < (std::end(v1) - nine));
  std::cout << "Nine in first half: " << std::boolalpha << nine_in_firsthalf << std::endl;
}

#include <iostream>
#include "adder.h"

int main(int argc, char* argv[]) {
  int value = my_math::add(10, 20);
  std::cout << "10 + 20 = " << value << std::endl;
  return EXIT_SUCCESS;
}
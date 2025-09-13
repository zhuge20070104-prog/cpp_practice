#include "olas_config.h"
#include "adder.h"
#include <iostream>


int main(int argc, char* argv[]) {
  std::cout << "OLAS version: " << OLAS_VERSION_MAJOR << "." << OLAS_VERSION_MINOR << std::endl;
  std::cout << "Using my_math: " << my_math::add(10.0f, 20.0f) << std::endl;
  return EXIT_SUCCESS;
}
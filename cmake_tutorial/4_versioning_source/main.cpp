#include "olas_config.h"
#include <iostream>

int main(int argc, char* argv[]) {
  std::cout << argv[0] << " Version: " << OLAS_VERSION_MAJOR << "." << OLAS_VERSION_MINOR << std::endl;
  std::cout << "Hello, ZhongLiang!" << std::endl;
  return EXIT_SUCCESS;
}
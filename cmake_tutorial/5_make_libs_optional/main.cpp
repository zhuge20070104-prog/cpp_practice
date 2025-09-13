#include "olas_config.h"
#include <iostream>


#ifdef USE_ADDER 
#include "adder.h"
#endif

int main(int argc, char* argv[]) {
  std::cout << "OLAS version: " << OLAS_VERSION_MAJOR << "." << OLAS_VERSION_MINOR << std::endl;
#ifdef USE_ADDER
  std::cout << "Using my_math: " << my_math::add(10.0f, 20.0f) << std::endl;
#else
  std::cout << "Not using my_math: " << 10.0f + 20.0f << std::endl;
#endif

  return EXIT_SUCCESS;
}
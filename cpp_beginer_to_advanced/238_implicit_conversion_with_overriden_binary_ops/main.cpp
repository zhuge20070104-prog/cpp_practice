#include <iostream>
#include "number.h"


int main(int argc, char* argv[]) {
    
    Number n1 {87};
    std::cout << "n1: " << n1 << '\n';
    std::cout << "n1 + 3.0: " << n1 + 3.0 << '\n';
    std::cout << "3.0 + n1: " << 3.0 - n1 << '\n';
    std::cout << "1.0 - n1: " << 1.0 - n1 << '\n';
    return EXIT_SUCCESS;
}
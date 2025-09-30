#include <iostream>
#include <cmath>
#include "number.h"


int main(int argc, char* argv[]) {

    Number n1 {91};
    Number n2 {71};

    std::cout << std::boolalpha;
    std::cout << "n1 < n2: " << (n1 < n2) << "\n";
    std::cout << "2 < n2: " << (2 < n2) << "\n";
    std::cout << "n1 > 7: " << (n1 > 7) << "\n";

    return EXIT_SUCCESS;
}
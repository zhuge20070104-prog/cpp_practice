#include <iostream>
#include <cstdlib>

#include "item.h"

int main(int argc, char* argv[]) {
    Item i1 {1, 6, 7};
    Item i2 {2, 1, 8};

    std::cout << std::boolalpha;

    std::cout << "i1 > i2: " << (i1 > i2) << "\n";

    std::cout << "(i1 <=> i2) > 0: " << ((i1 <=> i2) > 0) << "\n";

    std::cout << "(i1 >= i2): " << (i1 >= i2) << "\n";

    std::cout << "(i1 <= i2): " << (i1 <= i2) << "\n";
    std::cout << "(i1 < i2): " << (i1 < i2) << "\n";

    std::cout << "(i1 == i2): " << (i1 == i2) << "\n";

    std::cout << "(i1 != i2): " << (i1 != i2) << "\n";

    std::cout << "2 < i2: " << (2 < i2) << '\n';
    std::cout << "i1 > 2: " << (i1 > 2) << '\n';
    std::cout << "3 != i2: " << (3 != i2) << '\n';


    return EXIT_SUCCESS;
}
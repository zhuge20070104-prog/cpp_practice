#include <iostream>

#include "point.h"

int main(int argc, char* argv[]) {

    Point p1 {82.1, 82.1};
    Point p2 {87.6, 54.3};
    std::cout << p1 << '\n';
    std::cout << p2 << '\n';

    std::cout << std::boolalpha;

    std::cout << "p1 == p2: " << (p1 == p2) << '\n';
    std::cout << "p1 != p2: " << (p1 != p2) << '\n';

    std::cout << "82.1 == p1: " << (82.1 == p1) << '\n';
    std::cout << "p2 != 87.6: " << (p2 != 87.6) << '\n';
    
    return EXIT_SUCCESS;
}
#include <iostream>
#include "point.h"



int main(int argc, char* argv[]) {
    Point p1 {33.7, 89.6, 0};
    Point p2 {9.93, 8.73, 0};

    std::cout << "p1: " << p1 << '\n';
    std::cout << "p2: " << p2 << '\n';

    std::cin >> p1 >> p2;

    std::cout << "p1: " << p1 << '\n';
    std::cout << "p2: " << p2 << '\n';

    return EXIT_SUCCESS;
}
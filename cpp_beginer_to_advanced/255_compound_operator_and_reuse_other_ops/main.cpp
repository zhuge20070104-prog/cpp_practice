#include <iostream>
#include "point.h"



int main(int argc, char* argv[]) {
    Point p1 {3, 3, 0};
    Point p2 {5, 5, 0};

    p1 += p2;
    std::cout << "p1： " << p1 << '\n';

    p1 -= p2;
    std::cout << "p1: " << p1 << '\n';

    std::cout << "p1 + p2 + p1: " << p1 + p2 + p1 << '\n';
    std::cout << "p1 - p2 - p2: " << p1 - p2 - p2 << '\n';

    return EXIT_SUCCESS;
}
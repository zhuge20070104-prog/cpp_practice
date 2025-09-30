#include <iostream>
#include <cmath>
#include "point.h"



int main(int argc, char* argv[]) {

    Point p1 {2.7, 1.3};
    Point p2 {8.2, 0.7};

    std::cout << "p1 == p2: " << (p1 == p2) << "\n";
    std::cout << "p1 < p2: " << (p1 < p2) << "\n";
    std::cout << "p1 > p2: " << (p1 > p2) << "\n";
    std::cout << "p1!= p2: " << (p1 != p2) << "\n";
    std::cout << "p1 <= p2: " << (p1 <= p2) << "\n";
    std::cout << "p1 >= p2: " << (p1 >= p2) << "\n";

    std::cout << "p1: " << p1 << "\n";
    std::cout << "p2: " << p2 << "\n";

    return EXIT_SUCCESS;
}
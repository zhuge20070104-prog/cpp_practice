#include <iostream>
#include "point.h"


int main(int argc, char* argv[]) {
    Point p1 {22.8, 7.6};
    Point p2 {31.9, 2.5};

    std::cout << "p1 < p2: " << (p1 < p2) << "\n";
    std::cout << "p1 <= p2: " << (p1 <= p2) << "\n";
    std::cout << "p1 > p2: " << (p1 > p2) << "\n";
    std::cout << "p1 >= p2: " << (p1 >= p2) << "\n";
    std::cout << "p1 == p2: " << (p1 == p2) << "\n";
    std::cout << "p1 != p2: " << (p1 != p2) << "\n";

    std::cout << "2 != p2: " << (2 != p2) << "\n";
    std::cout << "p1 == 9: " << (p1 == 9) << "\n";
    return EXIT_SUCCESS;
}
#include <iostream>
#include "point.h"



int main(int argc, char* argv[]) {
    Point p1 {3, 3, 0};
    Point p2 {5, 5, 0};

    std::cout << "p2 + p1: " << p2 + p1 << '\n';
    std::cout << "p2 - p1: " << p2 - p1 << '\n';


    return EXIT_SUCCESS;
}
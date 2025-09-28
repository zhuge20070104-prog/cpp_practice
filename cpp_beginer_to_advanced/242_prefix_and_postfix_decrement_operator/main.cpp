#include <iostream>
#include "point.h"


int main(int argc, char* argv[]) {

    Point p1 {10, 10, 0};
    --p1;
    std::cout << "p1: " << p1 << '\n';

    std::cout << "p1--: " << p1-- << '\n';
    std::cout << "p1: " << p1 << '\n';
    
    return EXIT_SUCCESS;
}
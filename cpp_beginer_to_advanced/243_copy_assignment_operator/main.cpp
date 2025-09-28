#include <iostream>
#include "point.h"


int main(int argc, char* argv[]) {

    Point p1 {2, 8, 101};
    Point p2 {1, 7, 101};    

    p2 = p1;

    std::cout << "p1: " << p1 << '\n';
    std::cout << "p2: " << p2 << '\n';


    Point p3 = p2;
    std::cout << "p3: " << p3 << '\n';


    p1.operator=(p2).operator=(Point{0, 0, 0});

    std::cout << "p1: " << p1 << '\n';

    std::cout << "p2: " << p2 << '\n';

    return EXIT_SUCCESS;
}
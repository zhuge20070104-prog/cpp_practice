#include <iostream>
#include "point.h"



int main(int argc, char* argv[]) {

    Point p1 {2.1, 6.1, 0};
    ++p1;
    std::cout << "p1: " << p1 << '\n';
    return EXIT_SUCCESS;
}
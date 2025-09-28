#include <iostream>
#include "point.h"
#include "car.h"
#include "number.h"


int main(int argc, char* argv[]) {
    Point p1 {2.1, 3.6, 0};
    std::cout << "p1[0]: " << p1[0] << '\n';
    std::cout << "p1[1]: " << p1[1] << '\n';
    std::cout << "p1.operator[1]: " << p1.operator[](1) << '\n';
    return EXIT_SUCCESS;
}
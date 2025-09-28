#include <iostream>
#include "point.h"
#include "car.h"

int main(int argc, char* argv[]) {
    Point p1 {23, 48, 3243};
    Car c1 {"Toyota", 250};

    p1 = c1;

    std::cout << "p1: " << p1 << '\n';

    return EXIT_SUCCESS;
}
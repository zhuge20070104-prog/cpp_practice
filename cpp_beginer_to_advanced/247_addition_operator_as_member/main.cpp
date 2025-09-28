#include <iostream>
#include "point.h"
#include "car.h"
#include "number.h"


int main(int argc, char* argv[]) {
    Point p1 {50, 50, 0};
    Point p2 {50, 50, 0};

    (p1 + p2).print_info();
    return EXIT_SUCCESS;
}
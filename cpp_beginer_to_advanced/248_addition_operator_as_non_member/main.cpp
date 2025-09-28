#include <iostream>
#include "point.h"
#include "car.h"
#include "number.h"


int main(int argc, char* argv[]) {
    Point p1 {1, 1};
    Point p2 {2, 2};
    
    auto p3 { operator+(p1, p2) };
    auto p4 { p2 + p3 };
    p3.print_info();
    p4.print_info();
    return EXIT_SUCCESS;
}
#include <iostream>
#include "classes/point.h"
#include "classes/line.h"
#include "classes/cylinder.h"


int main(int argc, char* argv[]) {
    Geometry::Point p1 {2.1, 3.6};
    Geometry::Point p2 {3.6, 8.1};

    p1.print_info();

    Geometry::Line l1 {p1, p2};
    l1.print_info();

    Geometry::Cylinder c1 {2.1, 8.6};
    std::cout << "Volume of c1: " << c1.volume() << '\n';
    
    return EXIT_SUCCESS;
}


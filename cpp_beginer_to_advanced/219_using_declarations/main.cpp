#include <iostream>
#include "classes/point.h"
#include "classes/line.h"
#include "classes/cylinder.h"



int main(int argc, char* argv[]) {
    // this only imports the Point into the main(), other classes can't be used
    using Geometry::Point;
    Point p1;

    // whole namespace is imported - everything from the Geometry can be used in main()
    using namespace Geometry;
    Line l {p1, p1};
    Cylinder cylinder {2, 2};
    Point p2{};
    
    return EXIT_SUCCESS;
}


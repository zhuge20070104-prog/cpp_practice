#include <iostream>
#include "circle.h"
#include "oval.h"
#include "shape.h"

int main(int argc, char* argv[]) {
    std::cout << "sizeof(Shape): " << sizeof(Shape) << std::endl;
    std::cout << "sizeof(Oval): " << sizeof(Oval) << std::endl;
    std::cout << "sizeof(Circle): " << sizeof(Circle) << std::endl;

    Circle circle {4, "Stuff from Circle"};
    Shape shape {circle};
    shape.draw();

    return EXIT_SUCCESS;
}
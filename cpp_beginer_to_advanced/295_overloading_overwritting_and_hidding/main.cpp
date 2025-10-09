#include <iostream>
#include <memory>
#include "circle.h"
#include "oval.h"
#include "shape.h"


int main(int argc, char* argv[]) {
    Circle circle1 {5, "Shape from Circle1"};
    Oval oval1 {4, 3, "Shape from Oval1"};

    circle1.draw();

    Shape* shape_ptr {&oval1};
    // shape_ptr->draw(3, "Red");

    return EXIT_SUCCESS;
}
#include <iostream>
#include <memory>
#include "circle.h"
#include "oval.h"
#include "shape.h"


int main(int argc, char* argv[]) {
    Oval oval {4, 3, "Shape from Oval"};
    Shape* shape_ptr {&oval};
    shape_ptr->draw();
    return EXIT_SUCCESS;
}
#include <iostream>
#include <memory>
#include "shape.h"
#include "rectangle.h"


int main(int argc, char* argv[]) {
    std::shared_ptr<Shape> shape_ptr {std::make_shared<Rectangle>(7, 5, "Rectangle")}; 
    std::cout << "Surface of shape_ptr: " << shape_ptr->surface() << std::endl; 
    std::cout << "Perimeter of shape_ptr: " << shape_ptr->perimeter() << std::endl;
    std::cout << "typeid(*shape_ptr).name(): " << typeid(*shape_ptr).name() << std::endl;
    return EXIT_SUCCESS;
}
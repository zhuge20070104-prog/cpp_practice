#include <iostream>
#include "circle.h"
#include "oval.h"
#include "shape.h"

void draw_shape(Shape* shape) {
    shape->draw();
}

void draw_shape_ref(Shape& shape) {
    shape.draw();
}

int main(int argc, char* argv[]) {
    Shape shape;
    Oval oval;
    Circle circle;

    Shape* shape_ptr {&shape};
    shape_ptr->draw();

    shape_ptr = &oval;
    shape_ptr->draw();

    shape_ptr = &circle;
    shape_ptr->draw();
    
    Shape& shape_ref {circle};
    shape_ref.draw();

    draw_shape(&shape);
    draw_shape(&oval);
    draw_shape(&circle);

    draw_shape_ref(shape);
    draw_shape_ref(oval);
    draw_shape_ref(circle);


    Shape* shape_collection[] = {&shape, &oval, &circle};
    for(auto* shape: shape_collection) {
        std::cout << "LOOP: ";
        shape->draw();
    }
    
    return EXIT_SUCCESS;
}
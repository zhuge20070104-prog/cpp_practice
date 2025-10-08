#include <iostream>
#include "circle.h"
#include "oval.h"
#include "shape.h"

int main(int argc, char* argv[]) {
    Shape s1 {"Shape1"};
    s1.draw();

    Oval ov1 {5, 3, "Oval1"};
    ov1.draw();

    Circle c1 {4, "Circle1"};
    c1.draw();

    Shape* shape_ptr {&s1};
    shape_ptr->draw();

    shape_ptr = &ov1;
    shape_ptr->draw();

    shape_ptr = &c1;
    shape_ptr->draw();
    

    Shape& shape_ref {s1};
    shape_ref.draw();

    shape_ref = ov1;
    shape_ref.draw();

    shape_ref = c1;
    shape_ref.draw();
    return EXIT_SUCCESS;
}
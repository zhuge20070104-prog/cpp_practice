#include <iostream>
#include <memory>
#include "circle.h"
#include "oval.h"
#include "shape.h"


int main(int argc, char* argv[]) {
    Circle c1 {2, "Shape from Circle1"};
    Oval ov1 {4, 3, "Shape from Oval1"};
    Circle c2 {8, "Shape from Circle2"};
    Oval ov2 {6, 2, "Shape from Oval2"};
    Circle c3 {5, "Shape from Circle3"};
    Oval ov3 {11, 10, "Shape from Oval3"};

    std::cout << "sizeof(c1): " << sizeof(c1) << std::endl;
    std::cout << "sizeof(c2): " << sizeof(c2) << std::endl;
    std::cout << "sizeof(c3): " << sizeof(c3) << std::endl;
    std::cout << "sizeof(ov1): " << sizeof(ov1) << std::endl;
    std::cout << "sizeof(ov2): " << sizeof(ov2) << std::endl;
    std::cout << "sizeof(ov3): " << sizeof(ov3) << std::endl;

    Shape shape_array[] = {c1, ov1, c2, ov2, c3, ov3};
    // polymorphic behavior expected but derived objects are sliced off when copied to a
    // shape array
    for(auto& s: shape_array) {
        s.draw();
    }

    // slicing reduced the size of objects too
    for(auto& s: shape_array) {
        std::cout << "sizeof(s): " << sizeof(s) << std::endl;
    }

    Shape* shape_ptr_array[] = {&c1, &ov1, &c2, &ov2, &c3, &ov3};
    for(Shape* s: shape_ptr_array) {
        s->draw();
    }

    std::shared_ptr<Shape> shared_shape[] {
        std::make_shared<Circle>(5, "Circle"),
        std::make_shared<Oval>(3, 2, "Oval")
    };

    for(auto& shared: shared_shape) {
        shared->draw();
    }
    return EXIT_SUCCESS;
}
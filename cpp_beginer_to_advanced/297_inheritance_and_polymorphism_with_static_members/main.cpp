#include <iostream>
#include <memory>
#include "ellipse.h"
#include "shape.h"


int main(int argc, char* argv[]) {
   
    Shape shape1 {"Shape1"};
    Shape shape2 {"Shape2"};
    Shape shape3 {"Shape3"};

    std::cout << "shape3.get_count(): " << shape3.get_count() << "\n";

    Ellipse ellipse1 {4, 3, "Ellipse1"};
    std::cout << "Ellipse::m_count: " << Ellipse::m_count << "\n";

    Shape* shape_ptr[] {&shape1, &ellipse1};
    for(auto& shape: shape_ptr) {
        std::cout << "shape->get_count(): " << shape->get_count() << "\n";
    }

    return EXIT_SUCCESS;
}
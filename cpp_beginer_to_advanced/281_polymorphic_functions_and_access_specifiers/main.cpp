#include <iostream>
#include "ellipse.h"
#include <memory>


int main(int argc, char* argv[]) {
    std::shared_ptr<Shape> shape_ptr {std::make_shared<Ellipse>(4, 3, "Ellipse1")};

    shape_ptr->draw();


    Ellipse ellipse2 {7, 5, "Ellipse2"};
    ellipse2.func();


    // ellipse part is sliced off - static binding
    Shape shape1 {Ellipse{2, 1, "Ellipse3"}};

    shape1.draw();
    return EXIT_SUCCESS;
}
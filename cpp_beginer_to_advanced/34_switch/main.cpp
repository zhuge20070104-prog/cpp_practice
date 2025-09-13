#include <iostream>
#include <cassert>

int const Pen {10};
int const Marker {20};
int const Eraser {30};
int const Rectangle {40};
int const Circle {50};
int const Ellipse {60};


int main(int argc, char* argv[]) {
    int tool {Eraser};
    switch (tool) {
    case Pen: {
        std::cout << "Activate tool is Pen" << std::endl;
    }
        break;
    
    case Marker: {
        std::cout << "Activate tool is Marker" << std::endl;
    }
        break;
    
    case Eraser:
    case Rectangle:
    case Circle: {
        std::cout << "Drawing Shapes" << std::endl;
    }
        break;
    
    case Ellipse: {
        std::cout << "Activate tool is Ellipses" << std::endl;
    }
        break;
    default: {
        std::cout << "No match found" << std::endl;
    }
        break;
    }    

    std::cout << "Moving on" << std::endl;
    return EXIT_SUCCESS;
}
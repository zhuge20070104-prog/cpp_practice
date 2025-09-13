#include <iostream>
#include <cassert>

// Tools 
int const pen {10};
int const marker {20};
int const eraser {30};
int const rectangle {40};
int const circle {50};
int const ellipse {60};


int main(int argc, char* argv[]) {
    int tool {eraser};
    if(tool == pen) {
        std::cout << "activate tool is pen" << std::endl;
    } else if(tool == marker) {
        std::cout << "activate tool is marker" << std::endl;
    } else if(tool == eraser) {
        std::cout << "activate tool is eraser" << std::endl;
    } else if(tool == rectangle) {
        std::cout << "activate tool is rectangle" << std::endl;
    } else if(tool == circle) {
        std::cout << "activate tool is circle" << std::endl;
    } else if(tool == ellipse) {
        std::cout << "activate tool is ellipse" << std::endl;
    }

    std::cout << "moving on" << std::endl;
    return EXIT_SUCCESS;
}
#include <exception>
#include <iostream>
#include <string>
#include <string_view>
#include "box_container.h"


int main(int argc, char* argv[]) {
    BoxContainer box1;
    box1.add(1);
    box1.add(2);
    std::cout << "box1: " << box1 << std::endl;

    BoxContainer<double> box2;
    box2.add(1.1);
    box2.add(2.2);
    std::cout << "box2: " << box2 << std::endl;

    return EXIT_SUCCESS;
}

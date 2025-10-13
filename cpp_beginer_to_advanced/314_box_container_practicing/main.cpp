#include <exception>
#include <iostream>
#include <string>
#include <string_view>
#include "box_container.h"


int main(int argc, char* argv[]) {
    BoxContainer box1 {3};
    box1.add(2);
    box1.add(5);
    box1.add(3);
    box1.add(5);
    box1.add(4);
    box1.add(5);
    box1.add(6);
  
    BoxContainer box2;
    box2.add(9);
    box2.add(10);
    box2.add(11);

    box2 += box1;
    std::cout << "box2: " << box2 << std::endl;

    box2 = box1;
    std::cout << "box2: " << box2 << std::endl;

    std::cout << "box1 + box2: " << (box1 + box2) << std::endl;
    return EXIT_SUCCESS;
}

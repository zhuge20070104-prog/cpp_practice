#include <iostream>
#include <string>
#include "cylinder.h"


int main(int argc, char* argv[]) {
   
    Cylinder c1 {1.9, 2.6};
    c1.set_radius(2.0);
    c1.set_height(2.0);

    std::cout << "c1.get_radius(): " << c1.get_radius() << std::endl;
    std::cout << "c1.get_height(): " << c1.get_height() << std::endl;
    std::cout << "Volume of c1: " << c1.volume() << std::endl;
    
    return EXIT_SUCCESS;
}


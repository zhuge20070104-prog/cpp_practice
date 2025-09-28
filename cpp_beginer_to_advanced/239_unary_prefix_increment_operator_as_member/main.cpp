#include <iostream>
#include "point.h"



int main(int argc, char* argv[]) {

    Point p1 {2.1, -6.8};
    

    std::cout << "p1: " << p1 << '\n';

    ++p1;

    std::cout << "p1: " << p1 << '\n';

    for(std::size_t i{0}; i<20; ++i) {
        ++p1;
        std::cout << "p1: " << p1 << '\n';
    }
    
    return EXIT_SUCCESS;
}
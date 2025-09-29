#include <iostream>
#include "point.h"
#include "car.h"
#include "number.h"


int main(int argc, char* argv[]) {
    Point p1 {3.8, 9.2, 0};
    Point p2 {1.0, 6.7, 0};

    //  awkward, when << is a member of the Point class
    p1 << std::cout;
    
    // intuitive, operator<< as friend of Point, chaining of statements
    std::cout << "p1: " << p1 << ", " << p2 << '\n';

    return EXIT_SUCCESS;
}
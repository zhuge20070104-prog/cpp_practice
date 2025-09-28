#include <iostream>
#include "point.h"
#include "car.h"
#include "number.h"


int main(int argc, char* argv[]) {
    Point p1 {9.8, 5.1, 0};
    std::cout << "p1[0]: " << p1[0] << " p1[1]: " << p1[1] << '\n';

    // left syntax returns a reference to the m_x and m_y which can be used to modify the data
    p1[0] = 9.9;
    p1[1] = 6.6;

    std::cout << "p1[0]: " << p1[0] << " p1[1]: " << p1[1] << '\n';

    return EXIT_SUCCESS;
}
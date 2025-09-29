#include <iostream>
#include "number.h"

class Point {

public:
    Point(double x, double y):
        m_x{x}, m_y {y} {}
    
    operator Number() const {
        std::cout << "m_x convert to a number\n";
        return Number {static_cast<int>(m_x)}; 
    }
private: 
    double m_x {};
    double m_y {};
};

int main(int argc, char* argv[]) {

    Point p1 {8.2, 9.3};
    Point p2 {7.5, 6.8};

    std::cout << "p1 > p2: " << (p1 > p2) << "\n";
    std::cout << "p1 == p2: " << (p1 == p2) << "\n";
    return EXIT_SUCCESS;
}
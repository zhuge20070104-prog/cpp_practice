#include <iostream>
#include <string>


/*
 * we can initialize any object in C++ using () or {}
 *
 * {} - doesn't allow narrowing conversions
 * () - allows   
 */
 
class Point {
private: 
    double m_x {};
    double m_y {};

public:
    Point(double x, double y): m_x(x), m_y(y) {}

    std::string to_string() const {
        return "Point(" + std::to_string(m_x) + ", " + std::to_string(m_y) + ")";
    }
};

int main(int argc, char* argv[]) {
    Point p1 (5.9, 6.7);
    std::cout << p1.to_string() << std::endl;

    Point p2 {5.9, 6.7};
    std::cout << p2.to_string() << std::endl;

    int scores [] (1, 9, 8, 3);
    for(auto const& score: scores) {
        std::cout << score << std::endl;
    }

    return EXIT_SUCCESS;
}


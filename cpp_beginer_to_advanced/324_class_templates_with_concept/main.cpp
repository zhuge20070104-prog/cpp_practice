#include <exception>
#include <iostream>
#include <string>
#include <string_view>
#include "box_container.h"

template <typename T> requires std::is_arithmetic_v<T>
class Point {
public:
    Point() = default;
    Point(T x, T y): m_x{x}, m_y{y} {}
    friend std::ostream& operator<<(std::ostream& os, const Point<T>& point) {
        os << "Point: (" << point.m_x << ", " << point.m_y << ")";
        return os;
    }
private:
    T m_x{};
    T m_y{};
};


int main(int argc, char* argv[]) {
    
    // Point<char*> point1;
    Point<int> point2;
    Point<double> point3;
    BoxContainer<Point<int>> point_box;
    return EXIT_SUCCESS;
}

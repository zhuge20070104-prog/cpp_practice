#include <exception>
#include <iostream>
#include <string>
#include <string_view>
#include "box_container.h"

class Point {
    friend std::ostream& operator<<(std::ostream& os, const Point& point);
public:
    Point():Point{0.0, 0.0} {}
    Point(double x, double y): m_x{x}, m_y{y} {}
private:
    double m_x{};
    double m_y{};
};

std::ostream& operator<<(std::ostream& os, const Point& point) {
    os << "Point: (" << point.m_x << ", " << point.m_y << ")";
    return os;
}

int main(int argc, char* argv[]) {
    BoxContainer<int> int_box;
    int_box.add(2);
    int_box.add(5);
    std::cout << "int_box: " << int_box << std::endl;

    BoxContainer<double> double_box;
    double_box.add(8.3);
    double_box.add(2.2);
    double_box.add(2.9);
    std::cout << "double_box: " << double_box << std::endl;

    BoxContainer<Point> point_box;
    point_box.add(Point{2.1, 6.8});
    point_box.add(Point{8.6, 7.2});
    std::cout << "point_box: " << point_box << std::endl;

    BoxContainer<char> char_box;
    char_box.add('h');
    char_box.add('3');
    char_box.add('l');
    char_box.add('l');
    char_box.add('0');
    std::cout << "char_box: " << char_box << std::endl;

    BoxContainer<std::string> string_box;
    string_box.add("C++");
    string_box.add("Programming");

    std::cout << "string_box: " << string_box << std::endl;

    std::cout << "int_box.size(): " << int_box.size() << std::endl;
    std::cout << "double_box.size(): " << double_box.size() << std::endl;
    std::cout << "point_box.size(): " << point_box.size() << std::endl;
    std::cout << "char_box.size(): " << char_box.size() << std::endl;
    std::cout << "string_box.size(): " << string_box.size() << std::endl;

    return EXIT_SUCCESS;
}

#include <exception>
#include <iostream>
#include <string>
#include <string_view>
#include "box_container.h"

template <typename T, T threshold>
class Point {
public:
    Point(T x=0, T y=0);
private:
    T m_x{};
    T m_y{};
};

template <typename T, T threshold>
Point<T, threshold>::Point(T x, T y):
    m_x{x},
    m_y{y} {}


int main(int argc, char* argv[]) {
    BoxContainer<int, 10> int_box;
    int_box.add(2);
    int_box.add(3);
    int_box.add(33);
    int_box.add(9);
    int_box.add(7);
    
    std::cout << "int_box: " << int_box << std::endl;
    Point<double, 6.2> point;
    return EXIT_SUCCESS;
}

#include "point.h"
#include "number.h"
#include "car.h"

Point::Point(double x, double y, int data):
    m_x{x}, m_y{y}, point_data {new int{data}} {

}

Point::~Point() {
    delete point_data;
}


Point::Point(const& Number num):
    Point{static_cast<double>(num.get_wrappered_int()),
          static_cast<double>(num.get_wrappered_int()),
          0} {
    std::cout << "Using the Point constructor to convert\n";
}

void Point::operator=(const Car& right_car) {
    m_x = m_y = right_car.get_speed();
    *point_data = right_car.get_speed();
}

void Point::operator=(const Number& num) {
    m_x = m_y = num.get_wrappered_int();
    std::cout << "Using the copy assignment operator to convert\n";
}

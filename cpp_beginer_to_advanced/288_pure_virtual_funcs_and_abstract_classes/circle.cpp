#include "circle.h"

Circle::Circle(double radius, std::string_view desc): Shape(desc), m_radius(radius) {}

double Circle::perimeter() const {
    std::cout << "Circle::perimeter(): ";
    return 2 * PI * m_radius;
}

double Circle::surface() const {
    std::cout << "Circle::surface(): ";
    return PI * m_radius * m_radius;
}
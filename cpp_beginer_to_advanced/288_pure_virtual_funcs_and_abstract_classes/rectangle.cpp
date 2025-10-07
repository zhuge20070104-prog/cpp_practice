#include "rectangle.h"

Rectangle::Rectangle(double width, double height, std::string_view desc): Shape(desc), m_width(width), m_height(height) {}

double Rectangle::perimeter() const {
    std::cout << "Rectangle::perimeter(): ";
    return 2 * (m_width + m_height);
}

double Rectangle::surface() const {
    std::cout << "Rectangle::surface(): ";
    return m_width * m_height;
}
#include "ellipse.h"

Ellipse::Ellipse(): Ellipse(0.0, 0.0, "No Description") {}

Ellipse::Ellipse(double x_rad, double y_rad, std::string_view desc):
    Shape(desc), m_x_radius(x_rad), m_y_radius(y_rad) {
    ++m_count;
}
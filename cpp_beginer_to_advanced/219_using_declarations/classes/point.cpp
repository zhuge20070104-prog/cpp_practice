#include "point.h"

namespace Geometry {
    Point::Point(): Point{0.0, 0.0} {

    }

    Point::Point(double x, double y): m_x{x}, m_y{y} {
    }

    Point::~Point() = default;

    void Point::print_info() const {
        std::cout <<  m_x << ", " << m_y << '\n';
    }
}
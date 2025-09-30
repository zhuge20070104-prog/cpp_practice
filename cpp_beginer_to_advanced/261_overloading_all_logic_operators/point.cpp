#include "point.h"
#include <cmath>

double Point::length() const {
    return std::sqrt(pow(m_x - 0, 2) + pow(m_y - 0, 2) * 1.0);
}

bool Point::operator==(const Point& p) const {
    return (length() == p.length());
}

bool Point::operator!=(const Point& p) const {
    return (length() != p.length());
}

bool Point::operator<(const Point& p) const {
    return (length() < p.length());
}

bool Point::operator>(const Point& p) const {
    return (length() > p.length());
}

bool Point::operator<=(const Point& p) const {
    return (length() <= p.length());
}

bool Point::operator>=(const Point& p) const {
    return (length() >= p.length());
}
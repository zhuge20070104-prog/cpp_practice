#ifndef _FREDRIC_POINT_H_
#define _FREDRIC_POINT_H_

#include <iostream>

class Point {
public:
    Point() = default;
    Point(double x, double y): m_x{x}, m_y{y} {}
    Point(double x_y): Point{m_x, m_y} {}
    ~Point() = default;

    friend std::ostream& operator<<(std::ostream& os, const Point& p) {
        os << "Point: [" << p.m_x << ", " << p.m_y << ", " << p.length() << "]";
        return os;
    }

    bool operator==(const Point& p) const;
    bool operator!=(const Point& p) const;
    bool operator<(const Point& p) const;
    bool operator>(const Point& p) const;
    bool operator<=(const Point& p) const;
    bool operator>=(const Point& p) const;

private:
    double m_x {};
    double m_y {};

    double length() const;
};

#endif
#ifndef _FREDRIC_POINT_H_
#define _FREDRIC_POINT_H_

#include <iostream>
class Point {
public:
    Point() = default;
    Point(double x, double y): m_x{x}, m_y{y} {}
    Point(double x_y): Point{x_y, x_y} {}

    ~Point() = default;

    friend std::ostream& operator<<(std::ostream& os, const Point& p) {
        os << "Point: [" << p.m_x << ", " << p.m_y << ", " << p.length() << "]";
        return os;
    }


    bool operator==(const Point& p) const {
        return length() == p.length();
    }


    std::partial_ordering operator<=>(const Point& right) const {
        if(length() > right.length()) {
            return std::partial_ordering::greater;
        } else if(length() < right.length()) {
            return std::partial_ordering::less;
        } else if(length() == right.length()) {
            return std::partial_ordering::equivalent;
        } else {
            return std::partial_ordering::unordered;
        } 
    }


private:
    double m_x {};
    double m_y {};

    double length() const;
};

#endif
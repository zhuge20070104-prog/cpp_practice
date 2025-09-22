#ifndef _FREDRIC_POINT_HPP_
#define _FREDRIC_POINT_HPP_

#include <iostream>

namespace Geometry {

class Point {
public:
    Point();
    Point(double x, double y);
    void print_info() const;
    ~Point();
private:
    double m_x;
    double m_y;
};

}

#endif
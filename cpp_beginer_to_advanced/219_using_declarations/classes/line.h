#ifndef _FREDRIC_LINE_HPP_
#define _FREDRIC_LINE_HPP_

#include "point.h"

namespace Geometry {

class Line {
public:
    Line(const Point& start, const Point& end);
    void print_info() const;
private:
    Point m_start;
    Point m_end;
};

}

#endif
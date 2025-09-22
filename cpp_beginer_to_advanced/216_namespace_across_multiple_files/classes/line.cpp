#include "line.h"


namespace Geometry {
    Line::Line(const Point& start, const Point& end): m_start{start}, m_end{end} {
    }

    void Line::print_info() const {
        std::cout << "Line:\n";
        std::cout << "Start: ";
        m_start.print_info();
        std::cout << "End: ";
        m_end.print_info();
    }
}
#ifndef _FREDRIC_CIRCLE_H_
#define _FREDRIC_CIRCLE_H_

#include "oval.h"
#include <string_view>

class Circle: public Oval {
public:
    Circle() = default;
    Circle(double radius, std::string_view desc);
    ~Circle();

    void draw() const {
        std::cout << "Circle::draw() called: " << get_x_rad() <<
            ", " << m_description << "\n";
    }
};

#endif
#ifndef _FREDRIC_CIRCLE_H_
#define _FREDRIC_CIRCLE_H_

#include "oval.h"
#include <string_view>

class Circle: public Oval {
public:
    Circle() = default;
    Circle(double radius, std::string_view desc);
    virtual ~Circle();

    virtual void draw() const {
        std::cout << "Circle::draw() called: " << get_x_rad() <<
            ", " << m_description << "\n";
    }

    virtual void draw(int color_depth, std::string_view color) const override {
        std::cout << "Drawing a circle with color depth: " << color_depth 
        << " and color: " << color << '\n';
    }
};

#endif
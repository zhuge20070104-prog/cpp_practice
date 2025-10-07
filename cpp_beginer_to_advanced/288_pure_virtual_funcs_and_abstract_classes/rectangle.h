#ifndef _FREDRIC_RECTANGLE_H
#define _FREDRIC_RECTANGLE_H

#include "shape.h"

class Rectangle: public Shape {
public:
    Rectangle();
    Rectangle(double width, double height, std::string_view desc);
    virtual ~Rectangle() = default;

    virtual double perimeter() const override;
    virtual double surface() const override;

private:
    double m_width;
    double m_height;
};

#endif
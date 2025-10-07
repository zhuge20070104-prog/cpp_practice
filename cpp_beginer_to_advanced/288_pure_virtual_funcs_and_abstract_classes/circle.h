#ifndef _FREDRIC_CIRCLE_H
#define _FREDRIC_CIRCLE_H

#include <iostream>
#include "shape.h"

class Circle: public Shape {
public:
    Circle() = default;
    Circle(double radius, std::string_view desc);

    virtual ~Circle() = default;
    virtual double perimeter() const override;
    virtual double surface() const override;

private:
    double m_radius;
    inline static const double PI {3.14};
};

#endif
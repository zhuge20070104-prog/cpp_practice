#ifndef _FREDRIC_SHAPE_H
#define _FREDRIC_SHAPE_H

#include <iostream>

class Shape {
protected:
    Shape() = default;
    Shape(std::string_view desc);
public:
    virtual ~Shape() = default;

    virtual double perimeter() const = 0;
    virtual double surface() const = 0;

protected:
    std::string m_description;
};

#endif
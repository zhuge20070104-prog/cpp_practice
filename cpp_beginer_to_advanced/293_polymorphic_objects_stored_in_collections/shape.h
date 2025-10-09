#ifndef _FREDRIC_SHAPE_H_
#define _FREDRIC_SHAPE_H_

#include <iostream>
#include <string_view>

class Shape {
public:
    Shape() = default;
    Shape(std::string_view desc);
    virtual ~Shape();
    virtual void draw() const {
        std::cout << "Shape::draw() called: " << m_description << "\n";
    }

protected:
    std::string m_description;
};

#endif
#ifndef _FREDRIC_SHAPE_H
#define _FREDRIC_SHAPE_H

#include <iostream>
#include <string>
#include <string_view>

class Shape {
public:
    Shape(): Shape("No Description") {}

    Shape(std::string_view description);

    virtual ~Shape() = default;

    virtual void draw() const {
        std::cout << "Shape::draw() called: " << m_description << "\n";
    }

private:
    virtual void func() const {
        std::cout << "Shape::func() called: " << m_description << "\n";
    }

protected:
    std::string m_description;
};

#endif
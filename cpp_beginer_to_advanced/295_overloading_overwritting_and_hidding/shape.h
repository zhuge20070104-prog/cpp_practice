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
        std::cout << "Drawing a shape\n";
    }

    virtual void draw(int color_depth) const {
        std::cout << "Drawing a shape with color depth: " << color_depth << '\n';
    }
protected:
    std::string m_description;
};

#endif
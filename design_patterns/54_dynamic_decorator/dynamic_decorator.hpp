#ifndef _FREDRIC_DYNAMIC_DECORATOR_HPP_
#define _FREDRIC_DYNAMIC_DECORATOR_HPP_

#include "log.h"
#include <memory>
#include <string>
#include <array>
#include <numeric>
#include <iostream>
#include <sstream>
#include <memory>

struct Shape {
    virtual std::string str() const = 0;
};

struct Circle: Shape {
    float radius;
    Circle() {}

    Circle(float radius_): radius(radius_) {}

    std::string str() const override {
        std::ostringstream oss;
        oss << "A circle of radius: " << radius;
        return oss.str();
    }

    // resize 方法在子类中无法被调用
    void resize(float factor) {
        radius *= factor;
    }
};

struct Square: Shape {
    float side;
    Square() {}

    Square(float side_): side(side_) {}

    std::string str() const override {
        std::stringstream oss;
        oss << "A square with side: " << side;
        return oss.str();
    }
};

struct ColoredShape: Shape {
    std::shared_ptr<Shape> shape;
    std::string color;

    ColoredShape(std::shared_ptr<Shape> shape_, std::string const& color_): shape(shape_), color(color_) {}

    std::string str() const override {
        std::ostringstream oss;
        oss << shape->str() << " has the color " << color;
        return oss.str();
    }
};

struct TransparentShape: Shape {
    std::shared_ptr<Shape> shape;
    uint8_t transparency;

    TransparentShape(std::shared_ptr<Shape> shape_, uint8_t transparency_): shape(shape_), transparency(transparency_) {}

    std::string str() const override {
        std::stringstream oss;
        oss << shape->str() << " has: " <<
            static_cast<float>(transparency)/ 255.0f * 100.0f
            << "% transparency";
        return oss.str();
    }
};


#endif
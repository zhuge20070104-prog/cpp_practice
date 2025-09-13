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

template <typename T>
struct ColoredShape: T {
    static_assert(std::is_base_of<Shape, T>::value, "Template argument must be a shape");

    std::string color;

    // 必须有默认构造函数，否则不work
    ColoredShape() {}
    
    // 此处不能调用base类的成员函数，因为你并不知道 base类是什么
    template <typename ... Args>
    ColoredShape(std::string const& color_, Args ... args):
        T(std::forward<Args>(args)...), color(color_) {}
    
    std::string str() const override {
        std::ostringstream oss;
        oss << T::str() << " has the color " << color;
        return oss.str();
    }
};

template <typename T>
struct TransparentShape: T {
    static_assert(std::is_base_of<Shape, T>::value, "Template argument must be a shape");

    uint8_t transparency;

    template <typename ... Args>
    TransparentShape(uint8_t const transparency_, Args ... args):
        T(std::forward<Args>(args)...),  transparency(transparency_){

    }

    std::string str() const override {
        std::stringstream oss;
        oss << T::str() << " has "
            << static_cast<float>(transparency)/ 255.0f * 100.0f
            << "% transparency";
        return oss.str();
    }
};

#endif
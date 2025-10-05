#ifndef _FREDRIC_ELLIPSE_H
#define _FREDRIC_ELLIPSE_H

#include "shape.h"

class Ellipse: public Shape {
public:
    Ellipse();
    Ellipse(double x_rad, double y_rad, std::string_view desc);

    virtual ~Ellipse() = default;


private:
    virtual void draw() const override {
        std::cout << "Ellipse::draw() called: " << m_description << "\n";
    }
public:
    virtual void func() const override {
        std::cout << "Ellipse::func() called: " << m_description << "\n";
    }

private:
    double m_x_radius {};
    double m_y_radius {};
};

#endif
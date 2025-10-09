#ifndef _FREDRIC_OVAL_H_
#define _FREDRIC_OVAL_H_

#include <iostream>
#include "shape.h"
#include <string_view>


class Oval: public Shape {
public:
    Oval() = default;
    Oval(double x_rad, double y_rad, std::string_view desc);
    virtual ~Oval();

    virtual void draw() const {
        std::cout << "Oval::draw() called: "
            << m_x_rad << ", " << m_y_rad << ", "
            << m_description << "\n";
    }
protected:
    double get_x_rad() const {
        return m_x_rad;
    }
    double get_y_rad() const {
        return m_y_rad;
    }
private:
    double m_x_rad {0.0};
    double m_y_rad {0.0};
};

#endif
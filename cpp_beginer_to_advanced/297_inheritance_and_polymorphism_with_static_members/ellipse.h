#ifndef _FREDRIC_ELLIPSE_H
#define _FREDRIC_ELLIPSE_H

#include "shape.h"
#include <string_view>


class Ellipse: public Shape {
public:
    Ellipse();
    Ellipse(double x_rad, double y_rad, std::string_view desc);
    virtual ~Ellipse() {
        --m_count;
    }

    virtual int get_count() const override {
        return m_count;
    }

    inline static int m_count {0};

private:
    double m_x_radius {0.0};
    double m_y_radius {0.0};
};
#endif
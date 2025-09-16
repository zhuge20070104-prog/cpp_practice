#ifndef _FREDRIC_CYLINDER_H_
#define _FREDRIC_CYLINDER_H_

#include "consts.h"

class Cylinder {
public:
    Cylinder() = default;
    Cylinder(double base_radius, double height);
    
    double get_radius();
    double get_height();
    void set_radius(double base_radius);
    void set_height(double height);
    double volume();

private:
    double m_base_radius{};
    double m_height{};
};

#endif
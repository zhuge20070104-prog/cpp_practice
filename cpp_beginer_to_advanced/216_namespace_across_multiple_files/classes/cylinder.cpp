#include "cylinder.h"

namespace Geometry {
    Cylinder::Cylinder(double radius, double height): m_radius{radius}, m_height{height} {
    }

    double Cylinder::volume() const {
        return PI * m_radius * m_radius * m_height;
    }
}
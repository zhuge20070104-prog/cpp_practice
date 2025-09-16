#include "cylinder.h"

Cylinder::Cylinder(double base_radius, double height) {
    m_base_radius = base_radius;
    m_height = height;
}

double Cylinder::get_radius() {
    return m_base_radius;
}

double Cylinder::get_height() {
    return m_height;
}

void Cylinder::set_radius(double base_radius) {
    m_base_radius = base_radius;
}

void Cylinder::set_height(double height) {
    m_height = height;
}

double Cylinder::volume() {
    return PI * m_base_radius * m_base_radius * m_height;
}
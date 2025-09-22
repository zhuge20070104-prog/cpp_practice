#ifndef _FREDRIC_CYLINDER_HPP_
#define _FREDRIC_CYLINDER_HPP_


namespace Geometry {

class Cylinder {
public:
    Cylinder(double radius, double height);
    double volume() const;
    
private:
    inline static const double PI {3.14};
    double m_radius{1};
    double m_height{1};
};

}

#endif
#include <iostream>

const double PI {3.14};

class Cylinder {
private:
    double m_base_radius {1};
    double m_height {1};

public:
    Cylinder() = default;

    Cylinder(double base_radius, double height = 8);
    double get_radius() const;
    double get_height() const;

    void set_radius(double base_radius);
    void set_height(double height);
    double volume() const;
};

Cylinder::Cylinder(double base_radius, double height) {
    m_base_radius = base_radius;
    m_height = height;
    std::cout << "Parameterized called!\n";
}


double Cylinder::volume() const {
    return PI * m_base_radius * m_base_radius * m_height;
}

double Cylinder::get_radius() const {
    return m_base_radius;
}

double Cylinder::get_height() const {
    return m_height;
}

void Cylinder::set_radius(double base_radius) {
    m_base_radius = base_radius;
}

void Cylinder::set_height(double height) {
    m_height = height;
}

int main(int argc, char* argv[]) {
   
    Cylinder c1;
    std::cout << "Volume of c1: " << c1.volume() << std::endl;

    Cylinder c2 {2};
    std::cout << "Volume of c2: " << c2.volume() << std::endl;

    return EXIT_SUCCESS;
}


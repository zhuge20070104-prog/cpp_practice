#include <iostream>
#include <string>

const double PI {3.14};

class Cylinder {
public:
    Cylinder() {
        m_base_radius = 2.0;
        m_height = 2.0;
    }

    Cylinder(double base_radius, double height) {
        m_base_radius = base_radius;
        m_height = height;
    }

    double volume() {
        return PI * m_base_radius * m_base_radius * m_height;
    }

private:
    double m_base_radius{};
    double m_height{};
};

int main(int argc, char* argv[]) {
   
    Cylinder c1;
    std::cout << "volume of c1: " << c1.volume() << '\n';

    Cylinder c2 {3.2, 4.9};
    std::cout << "volume of c2: " << c2.volume() << '\n';
    
    return EXIT_SUCCESS;
}


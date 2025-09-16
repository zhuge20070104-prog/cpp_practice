#include <iostream>
#include <string>


const double PI {3.14};

class Cylinder {
public:
    Cylinder() = default;

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
    std::cout << "Volume of c1: " << c1.volume() << std::endl;
    
    return EXIT_SUCCESS;
}


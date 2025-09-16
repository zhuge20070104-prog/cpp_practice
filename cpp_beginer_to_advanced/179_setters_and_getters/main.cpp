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
    
    double get_radius() {
        return m_base_radius;
    }

    double get_height() {
        return m_height;
    }


    void set_radius(double base_radius) {
        m_base_radius = base_radius;
    }

    void set_height(double height) {
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
    c1.set_radius(2.0);
    c1.set_height(2.0);

    std::cout << "c1.get_radius(): " << c1.get_radius() << std::endl;
    std::cout << "c1.get_height(): " << c1.get_height() << std::endl;
    std::cout << "Volume of c1: " << c1.volume() << std::endl;
    
    return EXIT_SUCCESS;
}


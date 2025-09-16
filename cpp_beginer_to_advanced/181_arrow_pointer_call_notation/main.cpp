#include <iostream>

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
    double m_base_radius {};
    double m_height {};
};


int main(int argc, char* argv[]) {
   
    Cylinder c1 {5, 10};
    std::cout << "Volume of c1: " << c1.volume() << std::endl;

    Cylinder* p_c2 {new Cylinder(2, 4)};
    std::cout << "Volume of c2: " << (*p_c2).volume() << std::endl;

    // better way, arrow pointer operator
    std::cout << "Volume of c2: " << p_c2->volume() << std::endl;

    // Release the memory 
    delete p_c2;

    // Pointer to stack object
    Cylinder* p_c3 {&c1};
    std::cout << "Volume of c3: " << p_c3->volume() << std::endl;
    
    return EXIT_SUCCESS;
}


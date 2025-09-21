#include <iostream>


class Cylinder {
public:
    Cylinder() = default;

    Cylinder(double radius, double height):
        m_radius{radius}, m_height{height} {}
    
    double volume() const {
        return PI * m_radius * m_radius * m_height;
    }

private:
    double m_radius {};
    double m_height {};

    static inline const double PI {3.14};
};

int main(int argc, char* argv[]) {
    Cylinder c1 {2.0, 5.0};
    std::cout << "Volume of c1: " << c1.volume() << '\n';

    return EXIT_SUCCESS;
}


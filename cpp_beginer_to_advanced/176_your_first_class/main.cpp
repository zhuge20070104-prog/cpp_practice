#include <iostream>
#include <string>

const double PI {3.14};

class Cylinder {
public:
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
    
    return EXIT_SUCCESS;
}


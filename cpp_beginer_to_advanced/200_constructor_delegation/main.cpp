#include <iostream>


class Square {
private:
    double m_side {};
    std::string m_color {};
    int m_shading {};
    double m_position {};

public:
    explicit Square(double side);
    Square(double side, std::string color, int shading);

    ~Square() = default;
    double surface() const;
};

Square::Square(double side): Square{side, "black", 4} {
    std::cout << "Inside the one param constructor\n";
    m_position = 0.0;
    std::cout << "m_position initialized\nObject creation done!\n";
}


Square::Square(double side, std::string color, int shading) :
    m_side{side}, m_color{color}, m_shading{shading}
{
    std::cout << "Inside the three param constructor\n";
}

double Square::surface() const {
    return m_side * m_side;
}


int main(int argc, char* argv[]) {
    Square square {4};
   
    return EXIT_SUCCESS;
}


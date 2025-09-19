#include <iostream>

class Square {
private:
    double m_side {};

public:
    explicit Square(double side);
    ~Square() = default;
    double surface() const;
};


Square::Square(double side) :
    m_side{side}
{
}

double Square::surface() const {
    return m_side * m_side;
}

bool compare_squares(const Square& s1, const Square& s2) {
    return s1.surface() == s2.surface();
}


int main(int argc, char* argv[]) {
   Square square {4};

//    std::cout << compare_squares(square, 2) << '\n';

   std::cout << compare_squares(square, square) << '\n';

//    Square sq1;
   
    return EXIT_SUCCESS;
}


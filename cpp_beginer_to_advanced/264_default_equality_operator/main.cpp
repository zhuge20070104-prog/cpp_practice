#include <iostream>

class Item {

public:
    Item() = default;
    Item(int a, int b, int c): m_a{a}, m_b{c}, m_c{c} {}
    Item(int i): Item{i, i, i} {}

    // C++20 feature, compiler generates the == and != from this
    // performs memberwise comparison
    bool operator==(Item const& other) const = default;

private:
    int m_a{};
    int m_b{};
    int m_c{};
};


int main(int argc, char* argv[]) {

    Item i1 {2};
    Item i2 {2};

    std::cout << std::boolalpha;
    std::cout << "i1 == i2: " << (i1 == i2) << "\n";
    std::cout << "i1 != i2: " << (i1 != i2) << "\n";

    // implicit conversions work even on left operand when operator is defined as a member
    std::cout << "2.2 == i2: " << (2.2 == i2) << "\n";
    std::cout << "i1 == 2.2: " << (i1 == 2.2) << "\n";

    std::cout << "2.2 != i2: " << (2.2 != i2) << "\n";
    std::cout << "i1 != 2.2: " << (i1 != 2.2) << "\n";
    
    return EXIT_SUCCESS;
}
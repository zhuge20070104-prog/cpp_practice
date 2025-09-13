#include <iostream>

int main(int argc, char* argv[]) {
    
    char character1 {'a'};
    char character2 {'r'};
    char character3 {'r'};
    char character4 {'o'};
    char character5 {'w'};

    std::cout << character1 << std::endl;
    std::cout << character2 << std::endl;
    std::cout << character3 << std::endl;
    std::cout << character4 << std::endl;
    std::cout << character5 << std::endl;

    std::cout << std::endl;

    char value = 65; // A
    std::cout << "value: " << value << std::endl; // A
    std::cout << "value(int): " << static_cast<int>(value) << std::endl; // 65 

    return EXIT_SUCCESS;
}
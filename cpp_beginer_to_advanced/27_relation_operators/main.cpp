#include <iostream>

int main(int argc, char* argv[]) {
    int number1 {45};
    int number2 {60};

    std::cout << "number1: " << number1 << std::endl;
    std::cout << "number2: " << number2 << std::endl;

    std::cout << std::endl;
    std::cout << "Comparing variables" << std::endl;

    std::cout << std::boolalpha;
    std::cout << "number1 < number2: " << (number1 < number2) << std::endl;
    std::cout << "number1 <= number2: " << (number1 <= number2) << std::endl;
    std::cout << "number1 > number2: " << (number1 > number2) << std::endl; 
    std::cout << "number1 >= number2: " << (number1 >= number2) << std::endl; 
    std::cout << "number1 == number2: " << (number1 == number2) << std::endl; 
    std::cout << "number1!= number2: " << (number1!= number2) << std::endl; 

    std::cout << std::endl;
    std::cout << "Store comparison result and use it later" << std::endl;
    bool result = (number1 == number2);
    std::cout << number1 << "==" << number2 << ": " << result << std::endl;
    return EXIT_SUCCESS;
}
#include <iostream>

int main(int argc, char* argv[]) {
    // Addition
    int number1 {2};
    int number2 {7};

    int result = number1 + number2;
    std::cout << "result: " << result << std::endl;

    // Subtraction
    result = number2 - number1;
    std::cout << "result: " << result << std::endl;
    result = number1 - number2;
    std::cout << "result: " << result << std::endl;

    // Multiplication
    result = number1 * number2;
    std::cout << "result: " << result << std::endl;

    // Division
    result = number2/ number1;
    std::cout << "result: " << result << std::endl;

    // Modulus
    // 注意: 不能对浮点数取余， 没有任何意义
    result = number2 % number1;
    std::cout << "result: " << result << std::endl;

    result = 31 % 10;
    std::cout << "result: " << result << std::endl;

    return EXIT_SUCCESS;
}
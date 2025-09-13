#include <iostream>


int main(int argc, char* argv[]) {

    // Decimal 
    int number1 = 15;
    // Octal
    int number2 = 017;
    // Hexadecimal
    int number3 = 0x0f; 
    // Binary
    int number4 = 0b00001111;

    std::cout << "Number1 is: " << number1 << std::endl;
    std::cout << "Number2 is: " <<number2 << std::endl;
    std::cout << "Number3 is: " << number3 << std::endl;
    std::cout << "Number4 is: " << number4 << std::endl;

    return EXIT_SUCCESS;
}
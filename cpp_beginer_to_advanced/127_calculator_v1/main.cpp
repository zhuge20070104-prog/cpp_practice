#include <iostream>

int main(int argc, char* argv[]) {
    double first_number {5.0};
    double second_number {33.1};

    char c{'+'};

    switch (c) {
    case '+':
        std::cout << first_number << " + " << second_number << " = " << 
            first_number + second_number << std::endl;
        break;
    case '-':
        std::cout << first_number << " - " << second_number << " = " << 
            first_number - second_number << std::endl;
        break;
    case '*':
        std::cout << first_number << " * " << second_number << " = " << 
            first_number * second_number << std::endl;
        break;
    case '/':
        std::cout << first_number << " / " << second_number << " = " << 
            first_number / second_number << std::endl;
        break;
    default:
        break;
    }
}
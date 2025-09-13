#include <iostream>
#include <cstring>

int main(int argc, char* argv[]) {

    if(argc != 4) {
        std::cerr << "Program can only be called with 3 arguments like: " << std::endl;
        std::cerr << "./bin/main 3 + 5" << std::endl;
        std::cerr << "You called with: ";
        for(int i=0; i < argc; ++i) {
            std::cerr << argv[i] << " ";
        }
        std::cerr << std::endl;
        return EXIT_FAILURE;
    }

    double first_number {std::atof(argv[1])};
    double second_number {std::atof(argv[3])};
    if(first_number == 0.0 || second_number == 0.0) {
        std::cerr << "Please use valid numbers (different from zero) for first and second parameters" << std::endl;
        return EXIT_FAILURE;
    }

    // Grab the operation
    char const* operation {argv[2]};
    char c;

    if((std::strlen(operation) == 1) &&
        operation[0] == '+' || operation[0] == '-' ||
        operation[0] == '*' || operation[0] == '/') {
        c = operation[0];
    } else {
        std::cerr << operation << " is not a valid operation." << std::endl;
        return EXIT_FAILURE;
    }

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

    return EXIT_SUCCESS;
}
#include <iostream>

int add_number(int first_number, int second_number) {
    int sum = first_number + second_number;
    return sum;
}

int main(int argc, char* argv[]) {
    int first_number = 12;
    int second_number = 9;
    int sum = first_number + second_number;

    std::cout << "sum of two numbers 12 + 9 using statement: " << sum << std::endl;
    std::cout << "sum of two numbers 23 + 8 using function: " << add_number(23, 8) << std::endl;
    return EXIT_SUCCESS;
}
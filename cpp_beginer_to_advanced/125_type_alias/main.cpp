#include <iostream>

int main(int argc, char* argv[]) {
    using huge_int_t = unsigned long long int;
    huge_int_t huge_number = 123378997;

    std::cout << "sizeof(unsigned long long int): " << sizeof(unsigned long long int) << std::endl;
    std::cout << "sizeof(huge_int_t): " << sizeof(huge_int_t) << std::endl;
    std::cout << "huge_number: " << huge_number << std::endl;

    return EXIT_SUCCESS;
}
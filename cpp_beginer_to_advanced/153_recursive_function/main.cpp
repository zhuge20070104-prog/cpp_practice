#include <iostream>

// recursion - function calling itself
std::size_t sum_upto_zero(std::size_t value) {
    if(value != 0) {
        return value + sum_upto_zero(value - 1);
    }

    return 0;
}

int main(int argc, char* argv[]) {

    std::cout << sum_upto_zero(5) << '\n';
    return EXIT_SUCCESS;
}
#include <iostream>
#include "compare.h"
#include "operations.h"

int main(int argc, char* argv[]) {
    int maximum = max(134, 56);
    std::cout << "max: " << maximum << std::endl;

    int minimum = min(146, 23);
    std::cout << "min: " << minimum << std::endl;

    int x{4};
    int y{5};
    int result = incr_mult(x, y);
    std::cout << "result: " << result << std::endl;

    return EXIT_SUCCESS;
}
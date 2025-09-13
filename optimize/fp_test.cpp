#include "test_driver.h"
#include <iostream>

int test_fp(int, unsigned long);

int (*func[])(int, unsigned long) = {
    test_fp,
    0
};

int main(int argc, char* argv[]) {
    test_driver(func, argc, argv);
    return EXIT_SUCCESS;
}
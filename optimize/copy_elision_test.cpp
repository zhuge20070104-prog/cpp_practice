#include "test_driver.h"
#include <iostream>

int test_copy_elision(int, unsigned long);

int (*func[])(int, unsigned long) = {
    test_copy_elision,
    0
};

int main(int argc, char* argv[]) {
    test_driver(func, argc, argv);
    return EXIT_SUCCESS;
}
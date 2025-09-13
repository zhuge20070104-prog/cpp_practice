#include "test_driver.h"
#include <iostream>

int test_log(int, unsigned long);

int (*func[])(int, unsigned long) = {
    test_log,
    0
};

int main(int argc, char* argv[]) {
    test_driver(func, argc, argv);
    return EXIT_SUCCESS;
}
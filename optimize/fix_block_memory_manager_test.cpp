#include "test_driver.h"
#include <iostream>

int test_fixed_block_memory_manager(int, unsigned long);

int (*func[])(int, unsigned long) = {
    test_fixed_block_memory_manager,
    0
};

int main(int argc, char* argv[]) {
    test_driver(func, argc, argv);
    return EXIT_SUCCESS;
}
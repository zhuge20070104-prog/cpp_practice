#include <iostream>
#include <cstdlib>

#include "item.h"

/*
 * <=> is going to be deleted by the compiler if the class has members which don't implement
 * their own <=> operator, because compiler can't compare those member variables with other
 * types
 */

int main(int argc, char* argv[]) {
    Item i1 {1, 2, 3};
    Item i2 {1, 2, 4};

    std::cout << "(i1 <=> i2) != 0: " << ((i1 <=> i2) != 0) << "\n";
    return EXIT_SUCCESS;
}
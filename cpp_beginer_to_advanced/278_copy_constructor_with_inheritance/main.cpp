#include <iostream>

#include "person.h"
#include "engineer.h"
#include "civil_engineer.h"

int main(int argc, char* argv[]) {
    Engineer e1 {"Leon Dune", 24, "St. 121 NY 10937", 3};

    Engineer e2 {e1};
    std::cout << e2 << '\n';

    CivilEngineer ce1 {"Leon Dune", 24, "St. 121 NY 10937", 3, "Building Roads"};
    CivilEngineer ce2 {ce1};
    std::cout << ce2 << '\n';

    return EXIT_SUCCESS;
}
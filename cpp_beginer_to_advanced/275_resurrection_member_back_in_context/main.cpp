#include <iostream>

#include "person.h"
#include "engineer.h"
#include "civil_engineer.h"

int main(int argc, char* argv[]) {
    Engineer e1;
    CivilEngineer ce1;
    std::cout << e1 << '\n';
    std::cout << ce1 << '\n';

    ce1.build_road();

    return EXIT_SUCCESS;
}
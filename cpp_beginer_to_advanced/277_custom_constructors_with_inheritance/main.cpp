#include <iostream>

#include "person.h"
#include "engineer.h"
#include "civil_engineer.h"

int main(int argc, char* argv[]) {
    CivilEngineer ce1 {"Leon", 20, "St. 42 NY 1092", 2, "Bridge Builder"};
    std::cout << ce1 << '\n';
    return EXIT_SUCCESS;
}
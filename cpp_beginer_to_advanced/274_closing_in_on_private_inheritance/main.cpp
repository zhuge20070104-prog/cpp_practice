#include <iostream>

#include "person.h"
#include "engineer.h"
#include "civil_engineer.h"

int main(int argc, char* argv[]) {
    Person p1;
    std::cout << p1 << '\n';

    Engineer e1;
    e1.build_something();

    CivilEngineer ce1;
    ce1.build_something();
    ce1.build_road();

    return EXIT_SUCCESS;
}
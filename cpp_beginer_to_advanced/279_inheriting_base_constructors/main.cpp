#include <iostream>

#include "person.h"
#include "engineer.h"



int main(int argc, char* argv[]) {
    Engineer eng1 {"Dan Gray", 42, "Malbo, St 123, NY"};
    std::cout << eng1 << '\n';

    return EXIT_SUCCESS;
}
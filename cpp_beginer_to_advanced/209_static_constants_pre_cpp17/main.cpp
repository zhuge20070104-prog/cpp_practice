#include <iostream>


/*
 * before C++17 - only static ints and enums can be initialized in the class, other types
 * should be initialized in cpp file, for const non-static member variables - they can only be initialized in initializer list
 * of constructor
 *
 * init. order for static variables is not guaranteed, don't initialize one static member
 * with another static member, it might lead to crash
 */


int main(int argc, char* argv[]) {


    return EXIT_SUCCESS;
}


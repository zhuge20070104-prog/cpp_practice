#include <iostream>
#include "inline_variables_and_funcs.h"

void some_function();
void print_length_tu1();
void print_length_tu2();


int main(int argc, char* argv[]) {
    // inline function is not accessible in this TU
    /*some_function();*/
    
    print_length_tu1();
    print_length_tu2();

    test_from_header();
    return EXIT_SUCCESS;
}


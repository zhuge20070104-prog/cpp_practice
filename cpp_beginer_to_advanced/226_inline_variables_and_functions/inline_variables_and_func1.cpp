#include <iostream>
#include "inline_variables_and_funcs.h"

inline int length {2};

inline void some_func() {
    std::cout << length << ", address: " << &length << '\n';
}


void print_length_tu1() {
    std::cout << "Printing from TU1: ";
    some_func();
    test_from_header();
}

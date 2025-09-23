#include <iostream>

extern int global_variable;


// declaration for compiler - necessary, although the function has external linkage
void simple_function();

void print_global_from_other_file() {
    std::cout << ++global_variable << '\n';
    std::cout << "Simple function in other TU: ";
    simple_function();
}

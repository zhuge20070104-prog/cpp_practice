#include <iostream>


void simple_function() {
    int local_variable {10};
    std::cout << "Address of age: " << &local_variable << '\n';
}

const double global_const {9.8};

int global_variable {8};


// compiler needs to see the declaration - definition resides in other file
void print_global_from_other_file();

int main(int argc, char* argv[]) {
    simple_function();

    // global constants have internal linkage 
    std::cout << "global_const: " << global_const << '\n';

    // accessing from the same TU
    std::cout << global_variable << '\n';

    // accessing from another TU
    print_global_from_other_file();
    
    return EXIT_SUCCESS;
}


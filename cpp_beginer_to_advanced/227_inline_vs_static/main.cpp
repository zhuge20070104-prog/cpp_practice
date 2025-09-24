#include <iostream>


/*
 * inline names - combines all the definition in multiple TUs in one
 *
 * static or anonymous namespace names - doesn't combine the names, each TU will have separate
 * names, even though we defined names identically in all TUs
 *
 * prefer inline to save memory space
 */

void print_age_inline1();
void print_age_inline2();
void print_namespace1();
void print_namespace2();

int main(int argc, char* argv[]) {
    print_age_inline1();
    print_age_inline2();
    print_namespace1();
    print_namespace2();
    
    return EXIT_SUCCESS;
}


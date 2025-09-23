#include <iostream>


namespace Outer {
    int outer_int {200};

    namespace Inner {
        int inner_int {112};

        void print_outer_int() {
            // direct access
            std::cout << "Inner print outer_int: " << outer_int << '\n';
        }
    }

    void print_inner_int() {
        // inner:: is neccessary here, no direct access
        std::cout << "Outer print inner_int: " << Inner::inner_int << '\n';
    }
}

int main(int argc, char* argv[]) {
    Outer::Inner::print_outer_int();
    Outer::print_inner_int();
    return EXIT_SUCCESS;
}


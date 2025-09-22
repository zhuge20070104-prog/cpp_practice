#include <iostream>

void add(int a, int b) {
    std::cout << "Outer: " << a + b << '\n';
}


namespace non_global {
    void add(int a, int b) {
        std::cout << "Inner: " << a + b << '\n';
    }

    void do_something() {
        // to use the stuff from outside of namespace, use ::
        // without ::, the local add() will be called
        ::add(2, 2);
    }
}

int main(int argc, char* argv[]) {
    non_global::do_something();
    
    return EXIT_SUCCESS;
}


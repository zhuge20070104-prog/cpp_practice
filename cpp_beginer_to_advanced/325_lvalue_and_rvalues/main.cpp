#include <iostream>


int test() {
    return 0;
}

int main(int argc, char* argv[]) {
    // lvalues
    int x {2};
    int y {5};

    // // x+y is rvalue, can't take address of it
    // std::cout << &(x+y) << std::endl; // error
    // // test return an rvalue, can't take the address of it
    // std::cout << &(test()) << std::endl; // error
    return EXIT_SUCCESS;
}

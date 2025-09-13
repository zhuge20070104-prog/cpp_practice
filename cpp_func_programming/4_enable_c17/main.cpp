#include <iostream>

namespace A::B::C {
    int i;
};


int main(int argc, char* argv[]) {
    A::B::C::i = 42;
    std::cout << "Nested namespaces are available: " << A::B::C::i << std::endl;
    return EXIT_SUCCESS;
}

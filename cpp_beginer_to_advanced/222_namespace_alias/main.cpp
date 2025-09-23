#include <iostream>

namespace l1 {
    namespace l2 {
        namespace l3 {
            const int inside_l3 {3};
        }
    }
}

int main(int argc, char* argv[]) {
    // Creating a namespace alias
    namespace l3_namespace = l1::l2::l3;

    std::cout << l3_namespace::inside_l3 << '\n';
    
    return EXIT_SUCCESS;
}


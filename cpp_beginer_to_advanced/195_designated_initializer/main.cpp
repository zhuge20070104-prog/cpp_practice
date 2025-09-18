#include <iostream>
#include <initializer_list>
#include <cassert>

struct Component {
    double x {};
    double y {};
    double z {};
};

void print_comp(const Component& c) {
    std::cout << "x: " << c.x << '\n';
    std::cout << "y: " << c.y << '\n';
    std::cout << "z: " << c.z << '\n';
    std::cout << "-------\n";
}

int main(int argc, char* argv[]) {
    Component c1 {1, 2, 3};
    print_comp(c1);

    Component c2 {.x = 4, .y = 5, .z = 6};
    print_comp(c2);

    
    Component c3 {.y = 2};
    print_comp(c3);

    // Reorder is not allowed here, compile error
    // Component c4 {.z = 3, .x = 1};
    // print_comp(c4);

    return EXIT_SUCCESS;
}


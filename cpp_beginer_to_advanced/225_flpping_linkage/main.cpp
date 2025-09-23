#include <iostream>


/*
 * flipping linkage : changing external linkage to internal and vice versa
 *
 * to make a global const external : prefix it with extern, both in source TU and the
 * destination TU, where it'll be used
 *
 * to make a name external to internal : prefix it with static or wrap the name in an
 * anonymous namespace
 */


// internal linkage, but flipped to external linkage
extern const double light_speed {9.8};

void do_something_other();

// linkage flipped to internal from external
static void some_function() {
    std::cout << "static function" << '\n';
}


// another way of making function linkage to internal
// anonymous namespace
namespace {
    void test() {
        std::cout << 000 << '\n';
    }
}

int main(int argc, char* argv[]) {
    do_something_other();
    some_function();
    return EXIT_SUCCESS;
}


#include <iostream>
#include <concepts>
#include <type_traits>

double add(auto a, auto b) {
    return a + b;
}

int main(int argc, char* argv[]) {
    // concept failed - requires an integral type, add return a double - error
    // std::integral auto a {add(1, 6)};
    return EXIT_SUCCESS;
}


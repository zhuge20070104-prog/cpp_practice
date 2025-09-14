#include <iostream>
#include <concepts>
#include <type_traits>

template <typename T>
concept tiny_type = requires (T a) {
    // only enforces syntax, expression doesn't evaluate
    sizeof(T) <= 1223;
    // nested requirement - enforcing the expression to be checked
    requires sizeof(T) == 8;
};

tiny_type auto add(tiny_type auto a, tiny_type auto b) {
    return a + b;
}

template <typename T>
concept addable = requires (T a, T b) {
    // compound requirement - multiple statements
    { a + b } noexcept -> std::convertible_to<int>;
};

addable auto add_something(addable auto a, addable auto b) {
    return a + b;
}

int main(int argc, char* argv[]) {
    int a {1};
    int b {9};

    // sizeof(int) is not 8, compilation error
    // add(a, b);
    add_something(true, 2);
    return EXIT_SUCCESS;
}


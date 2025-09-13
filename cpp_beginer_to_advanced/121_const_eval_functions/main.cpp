#include <iostream>

// Evaluate this function at compile time.
// If you can't do that throw a complier error
// consteval只支持C++ 20,
// gcc 9.2.1不完全支持C++20
constexpr int get_value(int multiplier) {
    return 3 * multiplier;
}

int main(int argc, char* argv[]) {
    int result = get_value(4);
    std::cout << "const eval function return value: " << result << std::endl;
    int some_var {5};
    // result = get_value(some_var);
    return EXIT_SUCCESS;
}
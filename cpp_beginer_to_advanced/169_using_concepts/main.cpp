#include <iostream>
#include <concepts>

template <typename T>
T sum(T a, T b) requires std::integral<T> {
    return a + b;
}

int main(int argc, char* argv[]) {
    std::cout << "sum(2, 2): " << sum(2, 2) << '\n';
    // Only integral types can be used to call sum
    // sum(3, 9.8); 
    return EXIT_SUCCESS;
}


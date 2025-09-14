#include <iostream>
#include <concepts>
#include <type_traits>


template <typename T>
concept int_only = requires (T t) {
    requires sizeof(T) == 4;
};


template <typename T>
T add(T a, T b) requires std::integral<T> || std::floating_point<T> && int_only<T> {
    return a + b;
}

int main(int argc, char* argv[]) {
    // either integral or floating point can be passed
    add(2.2f, 2.9f);
    add('a', 'b');
    return EXIT_SUCCESS;
}


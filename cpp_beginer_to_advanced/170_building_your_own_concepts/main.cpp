#include <iostream>
#include <concepts>
#include <type_traits>

template <typename T>
concept doubles_only = std::is_floating_point_v<T>;

template <typename T> 
concept mutipliable = requires(T a, T b) {
    a * b;
    --a;
    ++a;
    a += 1;
};


doubles_only auto sum_doubles(doubles_only auto a, doubles_only auto b) {
    return a + b;
}

template <mutipliable T, mutipliable P>
auto multiply(T a, P b) {
    ++a;
    ++b;
    return a * b;
}
 

int main(int argc, char* argv[]) {
    sum_doubles(2.91, 2.2);
    sum_doubles(2.91f, 2.2f);

    multiply<int, double>(2, 2.2);
    return EXIT_SUCCESS;
}


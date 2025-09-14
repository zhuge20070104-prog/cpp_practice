#include <iostream>

template <typename T, typename P>
auto sum_c11(T a, P b) -> decltype(a+b) {
    return a + b;
}

auto sum(auto a, auto b) {
    return a + b;
}

int main(int argc, char* argv[]) {

    std::cout << sum(20, 20.2) << '\n';
    std::cout << sum_c11(20, 20.2) << '\n';

    return EXIT_SUCCESS;
}
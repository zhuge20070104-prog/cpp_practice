#include <iostream>

template <typename T, typename P>
auto maximum(T a, P b) {
    return (a > b) ? a : b;
}

int main(int argc, char* argv[]) {

    std::cout << "sizeof(maximum(2, 3.2)): " << sizeof(maximum(2, 3.2)) << '\n';
    std::cout << "maximum(2, 3.2): " << maximum(2, 3.2) << '\n';

    // we can explicitly specify the type of template parameters - implicit conversion
    std::cout << "sizeof(maximum<int, int>(2, 3.2)): " << sizeof(maximum<int, int>(2, 3.2)) << '\n';
    std::cout << "maximum<int, int>(2, 3.2): " << maximum<int, int>(2, 3.2) << '\n';

    return EXIT_SUCCESS;
}
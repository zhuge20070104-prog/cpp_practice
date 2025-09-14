#include <iostream>


template <typename T, typename P>
decltype(auto) maximum(T a, P b) {
    return (a > b) ? a : b;
}

int main(int argc, char* argv[]) {

    std::cout << "maximum(2, 8): " << maximum(2, 8) << '\n';

    return EXIT_SUCCESS;
}


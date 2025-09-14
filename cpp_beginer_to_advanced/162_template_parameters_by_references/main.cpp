#include <iostream>
#include <string>

template <typename T>
const T& maximum(const T& a, const T& b) {
    std::cout << "maximum a: " << &a << '\n';
    std::cout << "maximum b: " << &b << '\n';
    return (a > b) ? a : b;
}

int main(int argc, char* argv[]) {

    int a {2};
    int b {3};

    maximum(a, b);

    std::cout << "main a: " << &a << '\n';
    std::cout << "main b: " << &b << '\n';
    
    return EXIT_SUCCESS;
}
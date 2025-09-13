#include <iostream>

int max(int* a, int* b) {
    std::cout << "max with int* called" << std::endl;
    return (*a> *b) ? *a: *b;
}

// int max(int const* a, int const* b) {
//     std::cout << "max with int const* called" << std::endl;
//     return (*a> *b) ? *a: *b;
// }

int max(int const* const a, int const* const b) {
    std::cout << "&a: " << &a << std::endl;
    std::cout << "&b: " << &b << std::endl;
    return (*a > *b)? *a: *b;
}

int main()
{
    int a {10};
    int b {12};
    int const* const p_a {&a};
    int const* const p_b {&b};
    std::cout << "&p_a: " << &p_a << std::endl;
    std::cout << "&p_b: " << &p_b << std::endl;

    int result = max(p_a, p_b);
    std::cout << "result: " << result << std::endl;

    return 0;
}

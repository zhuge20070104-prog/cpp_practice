#include <iostream>

int max(int& a, int& b) {
    std::cout << "max with int& called" << std::endl;

    // This change will be visible outside the function
    // a = 200
    return a>b ? a:b;
}

int max(int const& a, int const& b) {
    std::cout << "max with int const& called" << std::endl;
    // Can not change a and b through the reference
    // Will give a complier error
    return a>b ? a:b;
}

int main()
{
    int a {45};
    int b {85};
    int max1 = max(a, b);
    std::cout << "max1: " << max1 << std::endl;

    int const& ref_a = a;
    int const& ref_b = b;
    int max2 = max(ref_a, ref_b);
    std::cout << "max2: " << max2 << std::endl;

    return EXIT_SUCCESS;
}

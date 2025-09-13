#include <iostream>

int max(int a, int b) {
    std::cout << "int overload called" << std::endl;
    return (a>b) ? a: b;
}

double max(double a, double b) {
    std::cout << "double overload called" << std::endl;
    return (a>b)? a: b;
}

double max(int a, double b) {
    std::cout << "(int, double) overload called" << std::endl;
    return (a>b)? a: b;
}

double max(double a, int b) {
    std::cout << "(double, int) overload called" << std::endl;
    return (a>b)? a: b;
}

double max(double a, int b, int c) {
    std::cout << "(double, int, int) overload called" << std::endl;
    int max_bc = (b>c)? b: c;

    return (a>max_bc)? a: max_bc;
}

std::string_view max(std::string_view a, std::string_view b) {
    std::cout << "(string_view, string_view) overload called" << std::endl;
    return (a>b)? a: b;
}


int main()
{
    int x{4};
    int y{9};
    double a{5.4};
    double b{7.4};
    auto result = max(b, x, y);
    auto max_str = max("Hello", "World");
    std::cout << "max_result: " << result << std::endl;
    std::cout << "max_str: " << max_str << std::endl;

    return 0;
}

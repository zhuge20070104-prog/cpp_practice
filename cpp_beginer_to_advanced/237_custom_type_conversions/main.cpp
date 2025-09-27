#include <iostream>
#include "point.h"
#include "number.h"


double sum(double a, double b) {
    return a + b;
}

void use_point(const Point& p) {
    std::cout << "from func use_point: " << p << '\n';
}

int main(int argc, char* argv[]) {
    Number n1 {82};
    Number n2 {90};

    std::cout << "n1: " << n1 << '\n';
    std::cout << "n1 + n1: " << n1 + n1 << '\n';
    std::cout << "n2 - n1: " << n2 - n1 << '\n';
    std::cout << "n1 * n2: " << n1 * n2 << '\n';
    std::cout << "n1 / n2: " << n1 / n2 << '\n';
    std::cout << "n1 % n2: " << n1 % n2 << '\n';

    // conversion of n1 and n2 to a double, member operator double() called for conversion
    std::cout << "sum(n1, n2): " << sum(n1, n2) << '\n';
    // conversion of n1 to a Point
    use_point(n1);
    use_point(n2);

    return EXIT_SUCCESS;
}
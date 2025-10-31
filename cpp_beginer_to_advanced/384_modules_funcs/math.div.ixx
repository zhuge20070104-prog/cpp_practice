module;

#include <iostream>

export module math.div;

export void divide(double a, double b) {
    std::cout << a / b << '\n';
}
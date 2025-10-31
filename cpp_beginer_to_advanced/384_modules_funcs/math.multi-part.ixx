module;

#include <iostream>

export module math:multiply;

export void multiply(int a, int b) {
    std::cout << a * b << '\n';
}
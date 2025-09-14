#include <iostream>
#include <cstring>

template <typename T>
T maximum(T a, T b) {
    std::cout << "Non-pointer template overload called\n";
    return (a > b) ? a : b;
}

template <typename T> 
T* maximum(T* a, T* b) {
    std::cout << "Pointer template overload called\n";
    return (*a > *b)? a : b;
}

const char* maximum(const char* a, const char* b) {
    std::cout << "Normal overload called\n";
    return (std::strcmp(a, b) > 0) ? a : b;
}

int main(int argc, char* argv[]) {

    int i1 {39};
    int i2 {92};

    auto p_i1 {&i1};
    auto p_i2 {&i2};

    const char* h {"hello"};
    const char* w {"world"};

    std::cout << "maximum(h, w): " << maximum(h, w) << '\n';
    std::cout << "maximum(i1, i2): " << maximum(i1, i2) << '\n';
    std::cout << "*maximum(p_i1, p_i2): " << *maximum(p_i1, p_i2) << '\n';

    return EXIT_SUCCESS;
}
#include <iostream>

template <typename T, typename P>
auto maximum(T a, P b) -> decltype(a > b ? a: b);

int main(int argc, char* argv[]) {

  
    int a {21};
    double b {39.2};

    std::cout << maximum(a, b) << '\n';
    std::cout << "sizeof(decltype((a > b)? a: b)): " << sizeof(decltype((a > b)? a: b)) << '\n';
    
    decltype(a + b) c {92};
    std::cout << "sizeof(c): " << sizeof(c) << '\n';

    return EXIT_SUCCESS;
}


template <typename T, typename P>
auto maximum(T a, P b) -> decltype(a > b ? a: b) {
    return (a > b) ? a : b;
}
#include <iostream>

template <typename return_type, typename T, typename P>
return_type maximum(T a, P b) {
    return (a > b) ? a : b;
}

int main(int argc, char* argv[]) {

    // int is passed as the template argument - necessary for return type deduction
    // T and P will be deduced from the arguments
    
    auto result {maximum<int>(2, 5.8)};
    std::cout << "sizeof(result): " << sizeof(result) << '\n';
    std::cout << "result: " << result << '\n';

    return EXIT_SUCCESS;
}
#include <iostream>
#include <string>


template <typename T>
T maximum(T a, T b) {
    return (a > b) ? a : b;
}
 
int main(int argc, char* argv[]) {

    int a {281};
    int b {892};

    double d1 {22.8};
    double d2 {82.3};

    std::string s1 {"Hello"};
    std::string s2 {"World"};

    auto max_s1s2 {maximum<std::string>(s1, s2)};
    std::cout << "max_s1s2: " << max_s1s2 << '\n';

    auto max_ab {maximum(a, b)};
    std::cout << "max_ab: " << max_ab << '\n';

    auto max_d1d2 {maximum(d1, d2)};
    std::cout << "max_d1d2: " << max_d1d2 << '\n';


    auto max_ad1 {maximum<int>(a, d1)};
    std::cout << "max_ad1: " << max_ad1 << '\n';
    
    return EXIT_SUCCESS;
}
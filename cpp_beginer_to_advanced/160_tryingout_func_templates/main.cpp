#include <iostream>
#include <string>


template <typename T>
T maximum(T a, T b) {
    return (a > b) ? a : b;
}
 
int main(int argc, char* argv[]) {

    int x {22};
    int y {28};
    auto max{ maximum(x, y)};
    std::cout << "maximum(x, y): " << max << '\n';

    std::string s1 {"Hello"};
    std::string s2 {"World"};

    auto max_str{ maximum(s1, s2) };
    std::cout << "maximum(s1, s2): " << max_str << '\n';

    return EXIT_SUCCESS;
}
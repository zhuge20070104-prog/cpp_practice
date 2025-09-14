#include <iostream>
#include <type_traits>


template <typename T>
void is_integral(T num) {
    static_assert(std::is_integral_v<T>, "You should pass an integer!");
    std::cout << "You passed: " << num << '\n';
}


int main(int argc, char* argv[]) {

    std::cout << std::boolalpha;
    std::cout << "is_integral<int>: " << std::is_integral<int>::value << '\n';
    std::cout << "is_floating_point<int>: " << std::is_floating_point_v<int> << '\n';

    std::cout << "is_integral<char>: " << std::is_integral_v<char><< '\n';
    std::cout << "is_integral<long long int>: " << std::is_integral_v<long long int> << '\n';

    is_integral(21202);

    auto sum {
        []<typename T>(T a, T b) {
            static_assert(std::is_floating_point_v<T>, "Please pass a float");
            return a + b;
        }
    };

    std::cout << "sum(9.1, 29.6): " << sum(9.1, 29.6) << '\n';

    return EXIT_SUCCESS;
}
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <functional>

int factorial(int const input, int const sum = 1) {
    if(input > 1) {
        return factorial(input - 1, sum * input);
    }
    return sum;
}

template<int input, int sum = 1>
struct factorial_: factorial_<input-1, input * sum> {

};

template<int sum>
struct factorial_<1, sum> {
    enum {
        value = sum
    };
};

int main(int argc, char* argv[]) {
    std::cout << "5!= " << factorial(5) << std::endl;
    std::cout << "factorial_<4> " << factorial_<4>::value << std::endl;
    std::cout << "factorial_<5> " << factorial_<5>::value << std::endl;
    return EXIT_SUCCESS;
}

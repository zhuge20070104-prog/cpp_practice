#include <iostream>
#include <limits>
#include <math.h>


int main(int argc, char* argv[]) {
    double weight = 7.7;
    // floor and ceil
    std::cout << "Weight rounded to floor is: " << std::floor(weight) << std::endl;
    std::cout << "Weight rounded to ceil is: " << std::ceil(weight) << std::endl;

    // abs
    double savings = -5000;
    std::cout << "Abs of weight is: " << std::abs(weight) << std::endl;
    std::cout << "Abs of savings is: " << std::abs(savings) << std::endl;

    // exp e = 2.71828
    double exponential = std::exp(10);
    std::cout << "The exponential of 10 is: " << exponential << std::endl;

    // pow
    std::cout << "3 ^ 4 is: " << std::pow(3, 4) << std::endl;
    std::cout << "9 ^ 3 is: " << std::pow(9, 3) << std::endl;

    // log 以e 为底的自然对数
    std::cout << "Log; to get 54.59, you would evaluate e to the power of: "
        << std::log(54.59) << std::endl;
    
    std::cout << "To get 10000, you'd need to evaluate 10 to the power of: "
        << std::log10(10000) << std::endl;
    
    // sqrt 
    std::cout << "The square root of 81 is: " << std::sqrt(81) << std::endl;

    // round, 半数[0.5]以下会round到没有
    std::cout << "3.654 rounded to: " << std::round(3.654) << std::endl;
    std::cout << "2.5 rounded to: " << std::round(2.5) << std::endl;
    std::cout << "2.4 rounded to: " << std::round(2.4) << std::endl;

    return EXIT_SUCCESS;
}
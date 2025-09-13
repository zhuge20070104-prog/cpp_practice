#include <iostream>

int main(int argc, char* argv[]) {

    []() {
        std::cout << "Hello!\n";
    };

    // Lambda function without name, called instantly without name
    []() {
        std::cout << "Hello!\n";
    }();

    // Parameter list is not needed when parameters are not passed
    auto print_hello {
        [] {
            std::cout << "Hello!\n";
        }
    };

    // Calling a named lambda function
    print_hello();


    // With parameters, arguments passed at the direct call
    [](int a, int b) {
        std::cout << a + b << '\n';
    }(2, 10);


    // return value from lambda stored in double_sum then called with arguments
    auto double_sum {
        [](double a, double b) {
            return a + b;
        }
    };

    std::cout << double_sum(2.1, 2.2) << '\n';
    std::cout << double_sum(3.2, 4.8) << '\n';

    // lambda expression in a print statement
    std::cout << [](double a, double b) { return a + b;}(22, 1) << '\n';

    // Explictly specifying the return type of the lambda, implict conversion 
    // from double to int type
    auto force_int {
        [](double a, double b) -> int {
            return a + b;
        }
    };

    std::cout << force_int(2.2, 2.2) << '\n';
    std::cout << sizeof(force_int(2.2, 2.2)) << '\n';

    return EXIT_SUCCESS;
}
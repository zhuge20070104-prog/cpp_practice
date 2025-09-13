#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <functional>

// three levels of curry lambda 
auto add_curry = [](auto a) {
    return [a](auto b) {
        return [a,b](auto c) {
            return a + b + c;
        };
    };
};

int main(int argc, char* argv[]) {
    auto adder1 = add_curry(1);
    auto adder2 = adder1(10);
    auto adder_results = adder2(100);
    std::cout << "results: " << adder_results << std::endl;
    auto add_once = add_curry(990000)(9900)(99);
    std::cout << "once results: " << add_once << std::endl;
    return EXIT_SUCCESS;
}

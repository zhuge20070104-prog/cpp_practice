#include "rxcpp/rx.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <functional>

namespace rx_{
    using namespace rxcpp;
    using namespace rxcpp::sources;
    using namespace rxcpp::operators;
    using namespace rxcpp::util;
} // namespace rx


int main(int argc, char* argv[]) {
    std::vector<int> ages {9, 20, 13, 4, 5, 6, 10, 28, 19, 15, 60, 23, 47, 12, 19, 99};
    rx_::observable<>::iterate(ages).
        filter([](int age){
            return age >= 21;
        }). 
        count().
        subscribe(
            [](int count) {
                std::cout << "Number over 21 = " << count << std::endl;
            },
            []() {
                std::cout << "onCompleted" << std::endl;
            }
        );  

    return EXIT_SUCCESS;
}

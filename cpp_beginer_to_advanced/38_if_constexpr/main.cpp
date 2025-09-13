#include <iostream>
#include <map>
#include <functional>
#include <vector>
#include <algorithm>



int main(int argc, char* argv[]) {
    bool constexpr condition {false};
    if constexpr(condition) {
        std::cout << "condition is true" << std::endl;
    } else {
        std::cout << "condition is false" << std::endl;
    }
    return EXIT_SUCCESS;
}
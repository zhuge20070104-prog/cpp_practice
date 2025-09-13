#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <functional>

auto continuous_add = [](int initial, int add_by) {
    auto total = initial;
    return [total, add_by]() mutable {
        total += add_by;
        return total;
    };
};

int main(int argc, char* argv[]) {
    auto x = continuous_add(1000, 10);
    std::cout << x() << std::endl;
    std::cout << x() << std::endl;
    std::cout << x() << std::endl;
    std::cout << x() << std::endl;
    std::cout << x() << std::endl;
    return EXIT_SUCCESS;
}

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <functional>

// 闭包成员变量，先使用，再加1，每次都会+1
// 0, 1, 2, 3
auto incrementer = []() {
    auto increment = 0;
    return [increment]() mutable {
         return increment++;
    };
};

int main(int argc, char* argv[]) {
    auto my_inc = incrementer();
    std::cout << "my_inc: " << my_inc() << std::endl;
    std::cout << "my_inc: " << my_inc() << std::endl;
    std::cout << "my_inc: " << my_inc() << std::endl;
    std::cout << "my_inc: " << my_inc() << std::endl;
    return EXIT_SUCCESS;
}

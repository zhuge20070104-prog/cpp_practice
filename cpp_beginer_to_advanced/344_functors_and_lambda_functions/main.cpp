#include <exception>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <functional>

/*
 * lambda functions: are modelled using functors behind the scenes, compiler convert a lambda to the class
 * behind the scenes
 */

int main(int argc, char* argv[]) {
    auto result {[](int a, int b) {return a + b; } (2, 2)};
    std::cout << "result: " << result << std::endl;
    return EXIT_SUCCESS;    
}

#include <iostream>
auto process_number(int value) {
    // returning int literal
    if(value < 10) {
        return 22;
    } else {
        return 55;
    }
}

int main(int argc, char* argv[]) {
    auto result = process_number(17);
    std::cout << "result: " << result << std::endl;
    std::cout << "sizeof(result): " << sizeof(result) << std::endl;
    std::cout << "sizeof(int): " << sizeof(int) << std::endl;
    std::cout << "sizeof(double): " << sizeof(double) << std::endl;
    return EXIT_SUCCESS;
}
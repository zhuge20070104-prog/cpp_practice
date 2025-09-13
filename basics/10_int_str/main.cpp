#include <string>
#include <iostream>

int main(int argc, char* argv[]) {
    uint64_t timestamp = 1665371143404090500;
    std::cout << std::to_string(timestamp) << std::endl;
    auto ts_str = std::to_string(timestamp);
    std::cout << std::boolalpha << (ts_str == "1665371143404090500")  << std::endl;
    return EXIT_SUCCESS;
}
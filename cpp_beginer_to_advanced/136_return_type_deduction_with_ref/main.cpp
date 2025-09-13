#include <iostream>

auto& max(int& a, int& b) {
    if(a>b) {
        return a;
    } else {
        return b;
    }
}

int main(int argc, char* argv[]) {
    int x{10};
    int y{45};

    int& result = max(x, y);
    std::cout << "x: " << x << std::endl;
    std::cout << "y: " << y << std::endl;
    std::cout << "result: " << result << std::endl;
    std::cout << "&y: " << &y << std::endl;
    std::cout << "&result: " << &result << std::endl;
    return EXIT_SUCCESS;
}
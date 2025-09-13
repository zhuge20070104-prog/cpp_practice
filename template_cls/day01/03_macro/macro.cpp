#include <iostream>
#include <string>

using string = std::string;
#define MAX(T) T max_##T(T x, T y) {\
                                    return x>y? x: y; \
                                    }

MAX(int)
MAX(double)
MAX(string)

#define Max(T) max_##T

int main(int argc, char* argv[]) {
    int nx = 10, ny = 20;
    std::cout << Max(int)(nx, ny) << std::endl;
    double dx = 12.3, dy = 45.6;
    std::cout << Max(double)(dx, dy) << std::endl;
    string sx = "world", sy = "hello";
    std::cout << Max(string)(sx, sy) << std::endl;
    return EXIT_SUCCESS;
}

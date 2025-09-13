#include <iostream>
#include <string>

int max_int(int x, int y) {
    return x > y? x: y;
}

double max_double(double x, double y) {
    return x>y?x: y;
}

std::string max_string(std::string sx, std::string sy) {
    return sx>sy?sx: sy;
}

int main(int argc, char* argv[]) {
    int nx = 10, ny = 20;
    std::cout << max_int(nx, ny) << std::endl;

    double dx = 12.3, dy = 45.6;
    std::cout << max_double(dx, dy) << std::endl;

    std::string sx = "world", sy = "hello";
    std::cout << max_string(sx, sy) << std::endl;

    return EXIT_SUCCESS;
}
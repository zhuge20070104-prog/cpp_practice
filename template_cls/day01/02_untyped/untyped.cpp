#include <iostream>
#include <string>

#define Max(x, y) (x>y ? x: y)


int main(int argc, char* argv[]) {
    int nx = 10, ny = 20;
    std::cout << Max(nx, ny) << std::endl;

    double dx = 12.3, dy=45.6;
    std::cout << Max(dx, dy) << std::endl;

    std::string sx = "world", sy = "hello";
    std::cout << Max(sx, sy) << std::endl;

    char cx[256] = "world", cy[256] = "hello";
    std::cout << Max(cx, cy) << std::endl;
    // char* 类型的比较结果不对， 应该用strcmp

    return EXIT_SUCCESS;
}
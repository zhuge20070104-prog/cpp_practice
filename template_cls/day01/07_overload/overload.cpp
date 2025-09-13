#include <iostream>
void Max(int x, int y) {
    std::cout << "1: Max(int, int)" << std::endl;
}

template <typename T>
void Max(T x, T y) {
    std::cout << "2: Max(T, T)" << std::endl;
}

int main(int argc, char* argv[]) {
    int nx = 10, ny = 20;
    Max(nx, ny);
    // 调用模板版本
    Max<>(nx, ny);
    double dx = 12.3, dy = 45.6;
    // 匹配模板多一些，没有double版本
    Max(dx, dy);

    // 匹配int, int，因为没有匹配的模板 Tx, D y
    // 只能匹配非模板，用隐式类型转换转换为 int
    Max(nx, dy);
    return EXIT_SUCCESS;
}
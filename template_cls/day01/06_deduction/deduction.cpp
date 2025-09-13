#include <iostream>

template <typename T>
T Max(T x, T y) {
    return x>y ? x:y;
} 

template <typename T, typename D>
void Func(D x) {

}

template <typename R, typename T>
R Hum(T x) {
    R r;
    return r;
}

int main(int argc, char* argv[]) {
    int nx = 10, ny = 20;
    std::cout << Max(nx, ny) << std::endl;
    double dx = 12.3, dy = 45.6;
    std::cout << Max(dx, dy) << std::endl;
    std::string sx = "world", sy = "hello";
    std::cout << Max(sx, sy) << std::endl;
    Func<std::string>(nx);
    Max(nx, (int)dy);
    Hum<double>(nx);
    return EXIT_SUCCESS;
}
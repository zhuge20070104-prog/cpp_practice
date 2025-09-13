#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <functional>

template <typename T>
T cube(T const& value) {
    return value * value * value;
}

template <int to_cube>
struct cube_ {
    enum {
        value = to_cube * to_cube * to_cube
    };
};

int main(int argc, char* argv[]) {
    std::cout << "8 cubed = " << cube(8) << std::endl;
    std::cout << "5 cubed = " << cube_<5>::value << std::endl;
    return EXIT_SUCCESS;
}

#include <iostream>
#include "matplotlib.h"

namespace plot = matplotlibc;

int main(int argc, char* argv[]) {
    plot::matplotlib_t plt;
    std::vector<float> x {1.0f, 2.0f, 3.0f, 4.0f};
    std::vector<float> y {1.0f, 2.0f, 3.0f, 4.0f};
    plt.clf();
    plt.scatter(x, y, 50, {{"color", "green"}, {"linewidths", "20"}});
    plt.save("result.png");
    return EXIT_SUCCESS;
}
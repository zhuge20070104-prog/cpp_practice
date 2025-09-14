#include <iostream>


int main(int argc, char* argv[]) {

    auto add {
        []<typename T>(T a, T b) {
            return a + b;
        }
    };

    int a {2};
    int b {2};

    auto result {add(a, b)};
    std::cout << "result: " << result << '\n';

    return EXIT_SUCCESS;
}
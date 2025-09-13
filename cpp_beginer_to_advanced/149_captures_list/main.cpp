#include <iostream>

int main(int argc, char* argv[]) {

    int x {1};
    int y {1};

    // Capturing x and y by value, both are copies inside the lambda
    auto capture_list {
        [x, y]() {
            std::cout << "Inner x + y : " << x + y << '\n';
        }
    };

    for(std::size_t i=0; i<5; ++i) {
        capture_list();
        std::cout << "Outer x + y: " << x + y << '\n';
        ++x;
        ++y;
    }

    std::cout << '\n';

    auto capture_list_ref {
        [&x, &y]() {
            std::cout << "Inner x + y : " << x + y << '\n';
        }
    };

    for(std::size_t i=0; i<5; ++i) {
        capture_list_ref();
        std::cout << "Outer x + y: " << x + y << '\n';
        ++x;
        ++y;
    }

    return EXIT_SUCCESS;
}
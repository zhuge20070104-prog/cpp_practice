#include <iostream>

int main(int argc, char* argv[]) {

    int a {6};
    int b {8};

    // mutable need to make the lambda mutable, immutable by default when
    // captured by value
    auto capt_by_val {
        [=]() mutable {
            ++a;
            ++b;
        }
    };

    capt_by_val();
    std::cout << "a: " << a << ", b: " << b << '\n';

    auto capt_by_ref {
        [&] () {
            ++a;
            ++b;
        }
    };

    capt_by_ref();
    std::cout << "a: " << a << ", b: " << b << '\n';

    return EXIT_SUCCESS;
}
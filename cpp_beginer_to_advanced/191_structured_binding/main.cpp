#include <iostream>
#include <string_view>

struct Point {
    double x {};
    double y {};
};


void print_point(const Point p) {
    std::cout << "x: " << p.x << '\n';
    std::cout << "y: " << p.y << '\n';
}

int main(int argc, char* argv[]) {
    // call to constructor, x and y members are copied to a and b, no & appended to auto
    auto [a, b] {Point{}};
    std::cout << a << ' ' << b << '\n';
    // Initial point
    Point p {2.2, 8.6};

    // Structured binding using a reference, & necessary for this
    auto& [x, y] {p};

    // changes to the Point
    p.x = 0.1;
    p.y = 0.9;

    // changes reflected in x and y too - references
    std::cout << x << ' ' << y << '\n';

    // print the point
    print_point(p);

    // capturing a structured binding in the lambda
    auto func {
        [x] () {
            std::cout << "x in lambda: " << x << '\n';
        }
    };

    func();
    return EXIT_SUCCESS;
}


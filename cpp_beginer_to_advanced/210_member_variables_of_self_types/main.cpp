#include <iostream>


class Point {
    Point* point;

    static Point p;
    static const Point p1;

public:
    // this causes infinite constructor calls - use nullptr instead
    // Point(): point {new Point{}} {}
    Point(): point {nullptr} {}
};

int main(int argc, char* argv[]) {

    Point p {};
    std::cout << "Done\n";
    return EXIT_SUCCESS;
}


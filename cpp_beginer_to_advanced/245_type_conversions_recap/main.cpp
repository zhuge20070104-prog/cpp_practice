#include <iostream>
#include "point.h"
#include "car.h"
#include "number.h"

void do_something(const Point& p) {
    std::cout << "from_func: " << p << '\n';
}

int main(int argc, char* argv[]) {
    Point p1 {0, 0, 0};
    Number n1 {2};

    p1 = n1;

    do_something(n1);
    return EXIT_SUCCESS;
}
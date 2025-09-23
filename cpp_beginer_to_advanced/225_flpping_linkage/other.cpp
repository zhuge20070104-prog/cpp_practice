#include <iostream>

extern const double light_speed;

void some_function();

void test();


void do_something_other() {
    std::cout << "other file: " << light_speed << '\n';

    // some_function();

    // test();
}
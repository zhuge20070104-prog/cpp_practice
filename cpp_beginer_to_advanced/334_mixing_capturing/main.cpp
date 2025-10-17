#include <exception>
#include <iostream>
#include <string>
#include <string_view>


int main(int argc, char* argv[]) {
    int a {8};
    int b {9};
    int c {10};
    int d {11};

    // capture all by value and d by refrence
    auto func1 {[=, &d] () {}};

    // capture all by reference and b by value
    auto func2 {[&, b] () {}};

    // capture all syntax should come first - correct
    auto func4 {[&, a, c] () {}};
    
    return EXIT_SUCCESS;
}

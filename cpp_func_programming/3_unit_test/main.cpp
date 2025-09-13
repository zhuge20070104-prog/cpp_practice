#include "catch2/catch_all.hpp"
#include <iostream>

int fibonacci(int n) {
    if(n <= 1) {
        return n;
    }

    return fibonacci(n-1) + fibonacci(n-2);
}

TEST_CASE("Fibonacci series", "[fibonacci]") {
    REQUIRE(fibonacci(0) == 0);
    REQUIRE(fibonacci(1) == 1);
    REQUIRE(fibonacci(2) == 1);
    REQUIRE(fibonacci(3) == 2);
    REQUIRE(fibonacci(4) == 3);
    REQUIRE(fibonacci(5) == 5);
    REQUIRE(fibonacci(12) == 144);
}
#include <iostream>

/*
 * type template parameters - typename T, typename P etc., they are type placeholders
 *
 * non type template parameters - int T, double x etc., they are not placeholders for
 * types, they are placeholders for values, we can specify values for types, before
 * C++17 and C++17, we can only use int as non-type template parameter
 */


template <int thresold, typename T>
bool is_valid(T collection[], std::size_t size) {
    T sum {};
    for(std::size_t i{0}; i<size; ++i) {
        sum += collection[i];
    }

    return sum > thresold;
}

int main(int argc, char* argv[]) {

    double temperatures[] {10.0, 20.0, 30.0, 40.0, 50.0};
    auto result {is_valid<200, double>(temperatures, std::size(temperatures))};
    std::cout << "result: " << std::boolalpha << result << std::endl;
    
    return EXIT_SUCCESS;
}
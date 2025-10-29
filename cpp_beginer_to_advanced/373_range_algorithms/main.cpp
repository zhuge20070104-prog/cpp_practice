#include <iostream>
#include <algorithm>
#include <ranges>
#include <vector>

/**
 * algo working on iterator pairs
 * algo working on ranges
 *
 * algo working on ranges with iterator pairs - possible, they are constrained with concepts
 *
 * prefer ranges version of the algorithms
*/

template <typename T>
void print_collection(const T& collection) {
    for(auto const& element: collection) {
        std::cout << element << ' ';
    }
    std::cout << '\n';
}


int main(int argc, char* argv[]) {
    std::vector<int> vector {1, 8, 9, 2, 3, 5, 4};
    auto is_odd {[](int n) {
        return n % 2 != 0;
    }};

    auto result {std::ranges::all_of(vector, is_odd)};
    if(result) {
        std::cout << "All numbers are odd in vector" << std::endl;
    } else {
        std::cout << "Not all numbers are odd in vector" << std::endl;
    }

    auto func {[](int& n) { n*=3;}};
    auto result1 {std::ranges::for_each(vector, func)};

    print_collection(vector);
    std::ranges::sort(vector);
    print_collection(vector);

    auto result2 {std::ranges::find_if(vector, is_odd)};
    if(result2 != vector.end()) {
        std::cout << "Vector has at least one odd number: " << *result2 << std::endl;
    } else {
        std::cout << "Vector has no odd numbers" << std::endl;
    }

    std::ranges::copy(vector, std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    std::list<int> list {1, 8, 2};
    std::ranges::sort(list);
    print_collection(list);
    return EXIT_SUCCESS;
}
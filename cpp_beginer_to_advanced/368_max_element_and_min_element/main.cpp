#include <iostream>
#include <algorithm>


int main(int argc, char* argv[]) {
    int collection[] {1, 2, 3, 5, 4, 9, 6, 100};
    std::cout << "std::max_element(std::begin(collection), std::end(collection)): " 
        << *std::max_element(std::begin(collection), std::end(collection)) << std::endl;
    std::cout << "std::min_element(std::begin(collection), std::end(collection)): " 
        << *std::min_element(std::begin(collection), std::end(collection)) << std::endl;
    
    int number_to_find {8};
    auto distance {[number_to_find](int x, int y) {
        return (std::abs(x - number_to_find) < std::abs(y - number_to_find));
    }};

    // closest to 8 is 9   
    std::cout << "std::min_element(std::begin(collection), std::end(collection), distance): " 
       << *std::min_element(std::begin(collection), std::end(collection), distance) << std::endl;
    // farthest from 8 is 100
    std::cout << "std::max_element(std::begin(collection), std::end(collection), distance): " 
        << *std::max_element(std::begin(collection), std::end(collection), distance) << std::endl;
    
    // return a pair of iterators
    const auto& [near, far] {
        std::minmax_element(std::begin(collection), std::end(collection), distance)
    };

    std::cout << "near: " << *near << std::endl;
    std::cout << "far: " << *far << std::endl;
 
    return EXIT_SUCCESS;
}
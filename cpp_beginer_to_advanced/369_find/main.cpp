#include <iostream>
#include <algorithm>


int main(int argc, char* argv[]) {
    int collection[] {10, 5, 2};
    int element_to_find {2};
    auto result = std::find(std::begin(collection), std::end(collection), element_to_find);
    if(result != std::end(collection)) {
        std::cout << "Element found: " << *result << std::endl;
    } else {
        std::cout << "Element not found" << std::endl;
    }

    auto predicate {[](int n) {
        if(n%2 != 0) {
            return true;
        }
        return false;
    }};

    auto result_pred {std::find_if(std::begin(collection), std::end(collection), predicate)};
    if(result_pred != std::end(collection)) {
        std::cout << "At least one odd element found: " << *result_pred << std::endl;
    } else {
        std::cout << "No odd element found" << std::endl;
    }

    return EXIT_SUCCESS;
}
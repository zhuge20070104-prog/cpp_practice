#include <iostream>
#include <algorithm>

void print_collection(int* collection, std::size_t size) {
    for(std::size_t i {0}; i<size; ++i) {
        std::cout << collection[i] << " ";
    }
    std::cout << std::endl;
}

int main(int argc, char* argv[]) {
    int collection[] {5, 2, 1, 3, 8, 4};
    std::sort(std::begin(collection), std::end(collection));
    print_collection(collection, std::size(collection));

    std::sort(std::begin(collection), std::end(collection), std::greater<int>());
    print_collection(collection, std::size(collection));

    auto less {[](int a, int b) {
        return a < b;
    }};

    std::sort(std::begin(collection), std::end(collection), less);
    print_collection(collection, std::size(collection));
    
    return EXIT_SUCCESS;
}
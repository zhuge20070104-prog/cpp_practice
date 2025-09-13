#include <iostream>


int main(int argc, char* argv[]) {
    int scores[] = {1, 2, 5};

    auto print_count = [&scores] () {
        int count {std::size(scores)};
        std::cout << "sizeof(scores) = " << sizeof(scores) << std::endl;
        std::cout << "sizeof(scores[0]) = " << sizeof(scores[0]) << std::endl;
        std::cout << "count: " << count << std::endl;
        std::cout << std::endl;
    };

    auto old_convention = [&scores] () {
        std::cout << "old_convention before c++11" << std::endl;
        int count {sizeof(scores)/sizeof(scores[0])};
        for(int i=0; i<count; ++i) {
            std::cout <<"scores[" << i << "] = " << scores[i] << std::endl;
        }
        std::cout << std::endl;
    };

    auto range_based_for_loop = [&scores] () {
        std::cout << "range based for loop" << std::endl;
        for(auto i: scores) {
            std::cout << "value: " << i << std::endl;
        }
        std::cout << std::endl;
    };

    print_count();
    old_convention();
    range_based_for_loop();

    return EXIT_SUCCESS;
}
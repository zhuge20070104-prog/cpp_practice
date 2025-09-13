#include <iostream>

double const* find_max_address(double const scores[], std::size_t count);

int main(int argc, char* argv[]) {
    double array[] {1.0,2.0,3.0,45.0,5.0,6.0,7.0,8.0,79.0,10.0};
    double const* p_max = find_max_address(array, std::size(array));
    std::cout << "max: " << *p_max << std::endl;
    return EXIT_SUCCESS;
}

double const* find_max_address(double const scores[], std::size_t count) {
    std::size_t max_index{};
    double max{};

    for(std::size_t i=0; i<count; ++i) {
        if(scores[i] > max) {
            max = scores[i];
            max_index = i;
        }
    }
    return &scores[max_index];
}
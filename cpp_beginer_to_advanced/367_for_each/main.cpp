#include <iostream>
#include <algorithm>
#include <vector>

struct Sum {
    void operator()(int n) {
        sum += n;
    }
    int sum {0};
};


int main(int argc, char* argv[]) {
    std::vector<int> vector {1, 2, 3, 4, 5};
    
    auto print {[](int n) {
        std::cout << n << ' ';
    }};

    std::for_each(std::begin(vector), std::end(vector), print);
    std::cout << std::endl;

    auto modify_print {[](int& n){
        ++n;
        std::cout << n << ' ';
    }};

    std::for_each(std::begin(vector), std::end(vector), modify_print);
    std::cout << std::endl;

    // modified collection
    std::for_each(std::begin(vector), std::end(vector), print);
    std::cout << std::endl;
    
    Sum sum;
    sum = std::for_each(std::begin(vector), std::end(vector), sum);
    std::cout << "sum: " << sum.sum << std::endl;

    // another way of doing the same thing
    int our_result {0};
    std::for_each(std::begin(vector), std::end(vector), [&our_result](int n) {
        our_result += n;
    });
    std::cout << "our_result: " << our_result << std::endl;
    return EXIT_SUCCESS;
}
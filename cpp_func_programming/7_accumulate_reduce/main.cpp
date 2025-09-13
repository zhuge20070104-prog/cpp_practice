#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>


int main(int argc, char* argv[]) {
    auto render = [](auto const& collection) {
        for(auto const& val: collection) {
            std::cout << val << std::endl;
        }
    };

    std::vector<int> in_ {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int> out_;

    std::transform(in_.begin(), in_.end(), std::back_inserter(out_),    
        [](int const& val) {
            return val * 3;
        });
    
    std::cout << "transform: " << std::endl;
    render(out_);

    std::vector<int> filter_;
    // 过滤out_中的所有奇数，存入filter_
    std::copy_if(out_.begin(), out_.end(), std::back_inserter(filter_),
        [](int const& val) {
            return val % 2 != 0;
        });
    
    std::cout << "copy_if: " << std::endl;
    render(filter_);

    int sum = std::accumulate(filter_.begin(), filter_.end(), 0,
        [](int total, int current) {
            return total + current;
        });
    
    std::cout << "accumulate: " << std::endl;
    std::cout << "sum = " << sum << std::endl; 
    return EXIT_SUCCESS;
}

#include <iostream>
#include <vector>
#include <algorithm>


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
    return EXIT_SUCCESS;
}

#include <iostream>
#include <vector>
#include <algorithm>
#include <boost/foreach.hpp>
#include <functional>
#include <numeric>

int main(int argc, char* argv[]) {
    
    std::vector<int> nums(8, 2);
    std::partial_sum(nums.begin(), nums.end(), nums.begin());
    std::partial_sum(nums.begin(), nums.end(), nums.begin());
    
    std::for_each(nums.begin(), nums.end(), [](int const& ele) {
        std::cout << ele << "\n";
    });

    return EXIT_SUCCESS;
}
#include <iostream>
#include <vector>
#include <algorithm>
#include <boost/foreach.hpp>

int main(int argc, char* argv[]) {
    
    std::vector<int> nums {10,20,30,30,20,10,10,20};
    // remove之后的效果     10 30 30 10 10
    // iter_return 之后的10, 10, 20 就没有用了，
    // 需要std::erase掉那个范围
    std::cout << "Before remove: ";
    BOOST_FOREACH(auto const& ele, nums) {
        std::cout << ele << " ";
    };
    std::cout << "\n";

    std::cout << "After remove: ";
    auto iter_return = std::remove(nums.begin(), nums.end(), 20);
    std::for_each(nums.begin(), iter_return, [](auto const& ele) {
        std::cout << ele << " ";
    });
    std::cout << "\n";

    std::cout << "Redundunt values: ";
    std::for_each(iter_return, nums.end(), [](auto const& ele) {
        std::cout << ele << " ";
    });

    std::cout << "\n";
    return EXIT_SUCCESS;
}
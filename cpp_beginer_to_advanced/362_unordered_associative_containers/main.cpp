#include <iostream>
#include <functional>
#include <unordered_set>
#include <unordered_map>


int main(int argc, char* argv[]) {
    std::unordered_set<int> unordered_set_ {1, 1, 8, 6, 5, 3, 2};
    std::unordered_map<int, std::string> unordered_map_ {
        {2, "Two"},
        {1, "One"},
        {4, "Four"},
        {3, "Three"}
    };

    auto it_set {unordered_set_.begin()};
    while(it_set != unordered_set_.end()) {
        std::cout << *it_set << " ";
        ++it_set;
    }
    std::cout << std::endl;

    auto it_map {unordered_map_.begin()};
    while(it_map != unordered_map_.end()) {
        std::cout << it_map->first << ", " << it_map->second << std::endl;
        ++it_map;
    }
    std::cout << std::endl;
    return EXIT_SUCCESS;
}
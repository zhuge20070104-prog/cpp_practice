#include <iostream>
#include <functional>
#include <map>
#include <set>


template <typename T>
void print_container(const T& container) {
    auto it {container.begin()};
    while(it != container.end()) {
        std::cout << *it << " ";
        ++it;
    }
    std::cout << std::endl;
}


int main(int argc, char* argv[]) {
    std::multiset<int> ms1 {1, 1, 2, 3, 4, 2, 3};
    print_container(ms1);

    std::multimap<int, std::string> multi_map1 {
        {1, "data"},
        {1, "data"},
        {1, "data"},
        {1, "data"},
    };

    auto it {multi_map1.begin()};
    while(it != multi_map1.end()) {
        std::cout << it->first << ", " << it->second << std::endl;
        ++it;
    }
    std::cout << std::endl;

    return EXIT_SUCCESS;
}
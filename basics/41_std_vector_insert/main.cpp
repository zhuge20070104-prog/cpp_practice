#include <vector>
#include <iostream>
#include <algorithm>

int main(int argc, char* argv[]) {
    std::vector<int> a {1, 2, 3, 4};
    std::vector<int> b {5, 6};
    a.insert(a.end(), b.begin(), b.end());
    std::for_each(a.begin(), a.end(), [](int const& ele) {
        std::cout << ele << " ";
    });
    std::cout << std::endl;

    a.erase(a.begin()+1, a.end());
    a.shrink_to_fit();

    std::for_each(a.begin(), a.end(), [](int const& ele) {
        std::cout << ele << " ";
    });
    std::cout << std::endl;
    return EXIT_SUCCESS;
}
#include <iostream>
#include <functional>
#include <utility>
#include <vector>


int main(int argc, char* argv[]) {
    std::pair<int, std::string> pair1 {189237, "Daniel"};
    auto pair2 {std::make_pair(1923674, "Jacob")}; 
    std::cout << pair1.first << ' ' << pair1.second << std::endl;
    std::cout << pair2.first << ' ' << pair2.second << std::endl;

    auto [int_key, str_value] {pair1};
    std::cout << int_key << ' ' << str_value << std::endl;

    std::pair pair3 {2, 'a'};
    std::cout << pair3.first << ' ' << pair3.second << std::endl;

    std::vector<std::pair<int, std::string>> pair_vector {pair1, pair2, {2, "Hello"}};
    std::cout << pair_vector[0].first << ' ' << pair_vector[0].second << std::endl;

    for(auto const& pair_: pair_vector) {
        std::cout << "Pair: " << pair_.first << ' ' << pair_.second << std::endl;
    }

    for(auto& [key, value]: pair_vector) {
        std::cout << "Pair[key, value]: " << key << ' ' << value << std::endl;
    }
    
    return EXIT_SUCCESS;
}
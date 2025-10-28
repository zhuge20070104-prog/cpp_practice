#include <iostream>
#include <algorithm>
#include <vector>

template <typename T>
void print_collection(const T& collection) {
    auto it {collection.begin()};
    while(it != collection.end()) {
        std::cout << *it << " ";
        ++it;
    }
    std::cout << std::endl;
}


int main(int argc, char* argv[]) {
    std::vector<int> v_src {1, 8, 2, 6, 3, 4};
    std::vector<int> v_dest {9, 7};
    
    auto pred {[](int n) {
        return n*2 + n;
    }};


    std::transform(std::begin(v_src), std::end(v_src), std::begin(v_dest), pred);

    print_collection(v_src);
    print_collection(v_dest);

    std::cout << "v_dest.capacity(): " << v_dest.capacity() << std::endl;

    std::transform(std::begin(v_src), std::end(v_src), std::back_inserter(v_dest), pred);
    print_collection(v_dest);

    std::cout << "v_dest.capacity(): " << v_dest.capacity() << std::endl;

    return EXIT_SUCCESS;
}
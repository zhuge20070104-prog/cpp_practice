#include <iostream>
#include <functional>
#include <array>

template <typename Container>
void print_container(const Container& container) {
    auto it {container.begin()};

    while(it != container.end()) {
        std::cout << *it << " ";
        ++it;
    }
    std::cout << std::endl;
}


int main(int argc, char* argv[]) {
    std::array<int, 5> array {1, 8, 6, 3, 2};
    print_container(array);

    std::cout << "array[3]: " << array[3] << std::endl;
    std::cout << "array.at(3): " << array.at(3) << std::endl;

    std::cout << "array[33]: " << array[33] << std::endl; // no bound checking

    try {
        std::cout << "array.at(33): " << array.at(33) << std::endl;
    } catch(std::exception& ex) {
        std::cout << "Out of range index: " << ex.what() << std::endl;
    }

    array.front() = 11;
    array.back() = 22;

    print_container(array);

    auto raw_ptr {array.data()};
    while(raw_ptr != array.end()) {
        std::cout << *raw_ptr << " ";
        ++raw_ptr;
    }
    std::cout << std::endl;

    auto it_reverse {array.rbegin()};
    while(it_reverse != array.rend()) {
        std::cout << *it_reverse << " ";
        ++it_reverse;
    }

    std::cout << '\n';

    std::cout << "array.size(): " << array.size() << std::endl;
    std::cout << "array.max_size(): " << array.max_size() << std::endl;
    std::cout << "array.empty(): " << array.empty() << std::endl;

    array.fill(291);

    print_container(array);

    std::array<int, 5> array2 {};
    array = array2;

    print_container(array);
    print_container(array2);

    return EXIT_SUCCESS;
}
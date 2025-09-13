#include <iostream>
#include <list>
#include <algorithm>
#include <future>


template <typename T>
std::list<T> parallel_quick_sort(std::list<T> input) {
    if(input.empty()) {
        return input;
    }

    std::list<T> result;
    // splice的用法及参数请参考
    // https://en.cppreference.com/w/cpp/container/list/splice
    result.splice(result.begin(), input, input.begin());
    T const& pivot = *result.begin();
    auto divide_point = std::partition(input.begin(), input.end(), [&] (T const& t) {
        return t < pivot;
    });

    std::list<T> lower_part;
    lower_part.splice(lower_part.end(), input, input.begin(), divide_point);
    auto new_lower =std::async(&parallel_quick_sort<T>, std::move(lower_part));
    auto new_higher(parallel_quick_sort<T>(std::move(input)));

    result.splice(result.end(), new_higher);
    result.splice(result.begin(), new_lower.get());
    return result;
}

template <typename T>
void print_list(std::list<T> const& ls) {
    std::cout << "[";
    std::for_each(ls.begin(), ls.end(), [](T const& ele) {
        std::cout << ele << " ";
    });
    std::cout << "]\n";
}

int main(int argc, char* argv[]) {  
    std::list<int> src_list {3, 2, 7, 1, 8, 6, 4, 5};
    print_list(src_list);
    auto sorted_list = parallel_quick_sort(src_list);
    print_list(sorted_list);
    return EXIT_SUCCESS;
}
#include <vector>
#include <future>
#include <thread>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <functional>


template <typename Iterator, typename Func>
void parallel_for_each(Iterator first, Iterator last, Func f) {
    unsigned long const length = std::distance(first, last);
    if(!length) {
        return;
    }    

    unsigned long const min_per_thread = 25;
    if(length < (2*min_per_thread)) {
        std::for_each(first, last, f);
    } else {
        Iterator const mid_point = first + length /2;
        std::future<void> first_half = std::async(
            &parallel_for_each<Iterator, Func>,  first, mid_point, f
        );
        parallel_for_each(mid_point, last, f);
        first_half.get();
    }
}

int main(int argc, char* argv[]) {
    std::vector<int> v(100);
    for(std::size_t i = 0; i<100; ++i) {
        v[i] = i;
    }

    parallel_for_each(v.begin(), v.end(), [](int const& ele) {
        std::cout << ele << std::endl;
    });
    return EXIT_SUCCESS;
}
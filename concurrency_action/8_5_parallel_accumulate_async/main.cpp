#include <vector>
#include <future>
#include <thread>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <functional>


template <typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T init) {
    unsigned long const length = std::distance(first, last);
    unsigned long const max_chunk_size = 25;
    if(length <= max_chunk_size) {
        return std::accumulate(first, last, init);
    } else {
        Iterator mid_point = first;
        std::advance(mid_point, length /2);
        std::future<T> first_half_result = std::async(parallel_accumulate<Iterator, T>, first, mid_point, init);
        T second_half_result = parallel_accumulate(mid_point, last, T());
        return first_half_result.get() + second_half_result;
    }
}



int main(int argc, char* argv[]) {
    
    std::vector<int> arr {
        1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28
    };

    // std::vector<int> arr {
    //     1, 2, 3, 4, 5
    // };
    
    int res = parallel_accumulate(arr.begin(), arr.end(), 0);
    std::cout << "sum: " << res << std::endl;
    
    return EXIT_SUCCESS;
}
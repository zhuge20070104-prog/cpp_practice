#include "thread_pool.hpp"
#include <iostream>
#include <algorithm>
#include <numeric>


template <typename Iterator, typename T>
struct accumulate_block {
    T operator()(Iterator first, Iterator last) {
        return std::accumulate(first, last, T());
    }
};

template <typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T init) {
    unsigned long const length = std::distance(first, last);

    if(!length) {
        return init;
    }

    unsigned long const block_size = 25;
    unsigned long const num_blocks = (length + block_size - 1)/block_size;
    std::vector<std::future<T>> futures(num_blocks - 1);

    thread_pool pool;
    Iterator block_start = first;
    for(unsigned long i=0; i<num_blocks - 1; ++i) {
        Iterator block_end = block_start;
        std::advance(block_end, block_size);
        // 这里不能传引用，否则会产生竟态
        futures[i] = pool.submit([=]() {
            return accumulate_block<Iterator, T>()(block_start, block_end);
        });
        block_start = block_end;
    }

    T last_result = accumulate_block<Iterator, T>()(block_start, last);
    T result = init;
    for(unsigned long i=0; i<num_blocks - 1; ++i) {
        result += futures[i].get();
    }

    result += last_result;
    return result;
}

int main(int argc, char* argv[]) {
    std::vector<int> v(100);
    for(std::size_t i=0; i<100; ++i) {
        v[i] = i+1;
    }

    int res = parallel_accumulate(v.begin(), v.end(), 0);
    std::cout << "1 + 2 + ... + 100 = " << res << std::endl;
    return EXIT_SUCCESS;
}
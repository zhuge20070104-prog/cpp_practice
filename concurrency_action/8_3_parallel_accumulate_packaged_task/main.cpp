#include <vector>
#include <future>
#include <thread>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <functional>


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

    unsigned long const min_per_thread = 25;
    unsigned long const max_threads = (length + min_per_thread - 1) / min_per_thread;
    unsigned long const hardware_threads = std::thread::hardware_concurrency();

    unsigned long const num_threads = std::min(hardware_threads!=0? hardware_threads:2, max_threads);

    unsigned long const block_size = length/ num_threads;
    std::vector<std::future<T>> futures(num_threads-1);
    std::vector<std::thread> threads(num_threads - 1);

    Iterator block_start = first;
    for(unsigned long i=0; i<(num_threads -1); ++i) {
        Iterator block_end = block_start;
        std::advance(block_end, block_size);

        auto f = accumulate_block<Iterator, T>();
        std::packaged_task<T(Iterator, Iterator)> task(std::move(f));
        futures[i] = task.get_future();
        threads[i] = std::thread(std::move(task), block_start, block_end);
        block_start = block_end;
    }
    T last_result = accumulate_block<Iterator, T>()(block_start, last);

    std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
    T result = init;
    for(unsigned long i=0; i<num_threads - 1; ++i) {
        result += futures[i].get();
    }

    result += last_result;
    return result;
}



int main(int argc, char* argv[]) {
    
    // std::vector<int> arr {
    //     1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25
    // };

    std::vector<int> arr {
        1, 2, 3, 4, 5
    };
    
    int res = parallel_accumulate(arr.begin(), arr.end(), 0);
    std::cout << "sum: " << res << std::endl;
    
    return EXIT_SUCCESS;
}
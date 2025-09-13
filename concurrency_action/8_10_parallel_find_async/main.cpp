#include <vector>
#include <future>
#include <thread>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <functional>

template <typename Iterator, typename MatchType> 
Iterator parallel_find_impl(Iterator first, Iterator last, MatchType match, std::atomic<bool>& done) {
    try {
        unsigned long const length = std::distance(first, last);
        unsigned long const min_per_thread = 25;
        if(length < 2*min_per_thread) {
            for(;(first!=last) && !done.load(); ++first) {
                if(*first == match) {
                    done = true;
                    return first;
                }
            }

            return last;
        } else {
            Iterator const mid_point = first + (length/2);
            std::future<Iterator> async_result = std::async(
                &parallel_find_impl<Iterator, MatchType>, mid_point, last, match, std::ref(done)
            );

            Iterator const direct_result = parallel_find_impl(first, mid_point, match, done);
            return (direct_result == mid_point)? async_result.get(): direct_result;
        }
    } catch(...) {
        done = true;
        throw;
    }
}

template <typename Iterator, typename MatchType>
Iterator parallel_find(Iterator first, Iterator last, MatchType match) {
    std::atomic<bool> done(false);
    parallel_find_impl(first, last, match, done);
}


int main(int argc, char* argv[]) {
    std::vector<int> v(100);
    for(std::size_t i = 0; i<100; ++i) {
        v[i] = i + 1;
    }

    auto it = parallel_find(v.begin(), v.end(), 101);
    if(it != v.end()) {
        std::cout << "Found: " << *it << std::endl;
    } else {
        std::cout << "Not found!" << std::endl;
    }
    return EXIT_SUCCESS;
}
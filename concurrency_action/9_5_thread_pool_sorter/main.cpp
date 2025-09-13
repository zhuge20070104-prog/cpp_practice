#include "thread_pool.hpp"
#include <iostream>
#include <algorithm>
#include <numeric>
#include <list>
#include <chrono>

template <typename T>
struct  sorter {
    thread_pool pool;

    std::list<T> do_sort(std::list<T>& chunk_data) {
        if(chunk_data.empty()) {
            return chunk_data;
        }

        std::list<T> result;
        result.splice(result.begin(), chunk_data, chunk_data.begin());
        T const& partition_val = *result.begin();
        typename std::list<T>::iterator divide_point = std::partition(
            chunk_data.begin(), chunk_data.end(),
            [&](T const& val) {
                return val < partition_val;
            }
        );

        std::list<T> new_lower_chunk;
        new_lower_chunk.splice(new_lower_chunk.end(), 
            chunk_data, chunk_data.begin(), divide_point);
        
        std::future<std::list<T>> new_lower = pool.submit([this,&new_lower_chunk]() {
            return do_sort(new_lower_chunk);
        }); 

        std::list<T> new_higher(do_sort(chunk_data));
        result.splice(result.end(), new_higher);

        while(true) {
            std::future_status status = new_lower.wait_for(std::chrono::seconds(0));
            if(status == std::future_status::ready) {
                break;
            }
            pool.run_pending_task();
        }
        result.splice(result.begin(), new_lower.get());
        return result;
    }
};


template <typename T>
std::list<T> parallel_quick_sort(std::list<T> input) {
    if(input.empty()) {
        return input;
    }

    sorter<T> s;
    return s.do_sort(input);
}


int main(int argc, char* argv[]) {
    std::list<int> ls;

    for(std::size_t i=0; i<10000; ++i) {
        if(i < 5000) {
            ls.push_back(i + 5000);
        } else {
            ls.push_back(i-5000);
        }
    }


    std::for_each(ls.begin(), ls.end(), [](int const& ele){
        std::cout << ele << " ";
    });
    std::cout << std::endl;

    std::list<int> res = parallel_quick_sort(ls);

    std::cout << "After parallel_quick_sort, result: " << std::endl;
    std::for_each(res.begin(), res.end(), [](int const& ele){
        std::cout << ele << " ";
    });
    std::cout << std::endl;
    return EXIT_SUCCESS;
}
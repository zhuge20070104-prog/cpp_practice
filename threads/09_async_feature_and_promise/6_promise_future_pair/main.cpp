#include <iostream>
#include <thread>
#include <list>
#include <mutex>
#include <future>
#include <vector>
#include <functional>

using ulong = unsigned long;
int sum(std::vector<int>& v, std::promise<ulong>& prom) {
    ulong sum {0};
    for(int i=0; i<v.size(); ++i) {
        sum += v[i];
    }
    prom.set_value(sum);
}


void total(std::vector<std::future<ulong>>& futs, std::promise<ulong>& total_prom) {
    ulong total {0};
    
    for(auto& fut: futs) {
        total += fut.get();
    }
    total_prom.set_value(total);
}


int main(int argc, char* argv[]) {
    std::vector<std::vector<int>>  nums(8);

    int const ele_size = 1000'0000;
    for(int i=0; i<nums.size(); ++i) {
        for(int j=0; j<ele_size; ++j) {
            nums[i].push_back(j+1);
        }
    }

    std::vector<std::promise<ulong>> proms(nums.size());
    std::vector<std::future<ulong>> futs;
    std::vector<std::thread> threads;

    std::promise<ulong> total_prom;
    for(int i=0; i<nums.size(); ++i) {
        futs.push_back(proms[i].get_future());
        threads.push_back(std::thread(sum, std::ref(nums[i]), std::ref(proms[i])));
    }

    std::thread total_thread(total, std::ref(futs), std::ref(total_prom));
    std::cout << "Total is: " << total_prom.get_future().get() << std::endl;
    std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
    total_thread.join();
    return EXIT_SUCCESS;
}
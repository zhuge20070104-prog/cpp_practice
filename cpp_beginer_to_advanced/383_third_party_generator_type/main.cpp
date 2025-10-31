#include <iostream>
#include <coroutine>
#include "unique_generator.h"



unique_generator<int> do_work() {
    std::cout << "Resume after initial pause\n";
    co_yield 1;
    co_yield 2;
    co_yield 3;
}

unique_generator<int> infinite_number_stream(int start) {
    auto value {start};
    std::cout << "Infinite number stream: \n";
    for(int i{0};;++i) {
        co_yield value;
        ++value;
    }
}

unique_generator<int> range(int first, int last) {
    std::cout << "range sequence: \n";
    while(first != last) {
        co_yield first++;
    }
}


int main(int argc, char* argv[]) {
   
    auto task_generator {do_work()};
    auto it = task_generator.begin();
    while(it != task_generator.end()) {
        std::cout << *it << '\n';
        ++it;
    }
    std::cout << std::boolalpha << (it == task_generator.end()) << '\n';
    

    auto task_infinite_sequence {infinite_number_stream(1)};
    auto it_infinite = task_infinite_sequence.begin();
    for(unsigned int i{0}; i<10; ++i) {
        std::cout << *it_infinite << '\n';
        ++it_infinite;
    }

    auto task_range_sequence {range(20, 80)};
    auto it_range = task_range_sequence.begin();
    for(unsigned int i{0}; i<30; ++i) {
        std::cout << *it_range << '\n';
        ++it_range;
    }
    return EXIT_SUCCESS;
}
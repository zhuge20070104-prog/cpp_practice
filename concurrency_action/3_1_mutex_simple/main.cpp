#include <iostream>
#include <mutex>
#include <algorithm>
#include <thread>
#include <list>

std::list<int> some_list;
std::mutex some_mutex;

void add_to_list(int new_value) {
    std::lock_guard<std::mutex> guard(some_mutex);
    some_list.push_back(new_value);
}

bool list_contains(int value_to_find) {
    std::lock_guard<std::mutex> guard(some_mutex);
    return std::find(some_list.begin(), some_list.end(), value_to_find) != some_list.end();
}

int main(int argc, char* argv[]) {
    std::thread add_thread([&](){
        for(int i=0; i<10; ++i) {
            some_list.push_back(i);
            std::this_thread::sleep_for(std::chrono::nanoseconds(1));
        }
    });


    std::thread contains_thread([&](){
        std::cout << std::boolalpha << "list_contains(1): " << list_contains(1) << "\n"
            << "list_contains(5): " << list_contains(5) << std::endl;
    });
    add_thread.join();
    contains_thread.join();
    return EXIT_SUCCESS;
}
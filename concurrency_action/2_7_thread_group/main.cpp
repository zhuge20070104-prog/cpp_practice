#include <iostream>
#include <thread>
#include <utility>
#include <vector>
#include <algorithm>
#include <functional>

void do_work(unsigned id) {
    std::cout << "Work id: " << id << std::endl;
}

void f() {
    std::vector<std::thread> threads;
    for(unsigned i=0; i<20; ++i) {
        threads.push_back(std::thread(do_work, i));
    }

    std::for_each(threads.begin(), threads.end(), 
        std::mem_fn(&std::thread::join));
}

int main(int argc, char* argv[]) {
    f();
    return EXIT_SUCCESS;
}
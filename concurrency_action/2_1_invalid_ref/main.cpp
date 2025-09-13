#include <iostream>
#include <thread>
#include <chrono>
#include <fstream>

void do_something(int& i, std::ofstream& ofs) {
    ++i;
    ofs << i << "\n";
}


struct func {
    int& i;

    func(int& i_): i(i_) {}

    void operator()() {
        std::ofstream f("result.txt");
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        for(unsigned j=0; j<1000'000; ++j) {
            do_something(i, f);
        }
        f.flush();
        f.close();
    }
};

void oops() {
    int some_local_state = 0;
    func my_func(some_local_state);
    std::thread my_thread(my_func);
    my_thread.detach();
}

int main(int argc, char* argv[]) {
    oops();
    // 此处 some_local_state 已经过期，可能产生未定义的引用
    // my_thread 可能还在后台执行
    std::this_thread::sleep_for(std::chrono::milliseconds(6000));
    return EXIT_SUCCESS;
}
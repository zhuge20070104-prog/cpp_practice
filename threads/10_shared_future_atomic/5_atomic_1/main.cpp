#include <iostream>
#include <thread>
#include <atomic>


int main(int argc, char* argv[]) {
    // load, 原子方式读取
    // store，原子方式写入
    std::atomic<int> a1(1);
    std::atomic<int> a2(a1.load());
    
    a2.store(10);
    
    std::cout << "a1 = " << a1 << std::endl;
    std::cout << "a2 = " << a2 << std::endl; 

    return EXIT_SUCCESS;
}
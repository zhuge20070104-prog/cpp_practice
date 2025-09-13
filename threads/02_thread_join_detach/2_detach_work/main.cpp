#include <thread>
#include <iostream>
#include <fstream>
#include <chrono>

void my_print() {
    std::fstream ofs("./thread_text.txt", std::ios::out);
    ofs << "我的线程开始运行..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    ofs << "Sleep 完成..." << std::endl;
    ofs << "Detach验证..." << std::endl;
    ofs << "验证Detach真的好用..." << std::endl;
    ofs << "我的线程运行完毕..." << std::endl;
    ofs.flush();
    ofs.close();
}

int main(int argc, char* argv[]) {
    std::thread my_thread(my_print);
    // 验证C++运行时能帮助把线程执行完
    my_thread.join();
    std::cout << "Hello world" << std::endl;
    return EXIT_SUCCESS;
}
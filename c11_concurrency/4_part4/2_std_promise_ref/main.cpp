#include "boost/filesystem.hpp"
#include <iostream>
#include <thread>
#include <algorithm>
#include <vector>
#include <cassert>
#include <future>
#include "asyc_out.hpp"

void the_func(std::promise<std::string>& prms) {
    std::string str("Hello from future!");
    prms.set_value(str);
}

// std::promise也可以用过引用传递，引用传递的好处就是
// 你可以把prms.get_future放到任何位置，不用非要放到 thread启动之前
int main(int argc, char* argv[]) {  
    std::promise<std::string> prms;

    std::thread th(&the_func, std::ref(prms));
    std::cout << "Hello from main!\n";

    std::future<std::string> ftr = prms.get_future();
    std::string str = ftr.get();
    std::cout << str << std::endl;
    th.join();
    return EXIT_SUCCESS;
}
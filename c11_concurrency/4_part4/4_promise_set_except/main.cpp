#include "boost/filesystem.hpp"
#include <iostream>
#include <thread>
#include <algorithm>
#include <vector>
#include <cassert>
#include <future>
#include "asyc_out.hpp"

class the_func_exception: public std::exception{
public:
    const char* what() const  noexcept override {
        return "The func exception!";
    }
};

// catch(...)
// 捕获所有异常，我们并不关心捕获了哪个异常
// std::current_exception 获取当前异常
void the_func(std::promise<std::string>& prms) {
    try {
        std::string str("Hello from future!");
        throw the_func_exception();
        prms.set_value(str);
    } catch(...) {
        prms.set_exception(std::current_exception());
    }
}

// promise set 的exception到主线程会rethrow
// 我们需要处理这个exception
// ftr.get 会触发rethow 这个exception
int main(int argc, char* argv[]) {  
    std::promise<std::string> prms;

    std::thread th(&the_func, std::ref(prms));
    std::cout << "Hello from main!\n";

    std::future<std::string> ftr = prms.get_future();
    try {
        std::string str = ftr.get();
        std::cout << str << std::endl;
    } catch(std::exception const& ex) {
        std::cout << ex.what() << std::endl;
    }
 
    th.join();
    return EXIT_SUCCESS;
}
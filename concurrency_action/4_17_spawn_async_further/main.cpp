#include <iostream>
#include <list>
#include <algorithm>
#include <future>
#include <stdexcept>
#include <functional>


// 类似std::async的实现，使用std::promise实现
template<typename Func, typename... Args>
std::future<typename  std::result_of<Func(Args&&...)>::type>
spawn_async(Func&& func, Args&& ... args){
    using result_type = typename  std::result_of<Func(Args&&...)>::type;
    std::promise<result_type> p;
    auto res=p.get_future();
    std::thread t(
        [=, p=std::move(p)]() mutable{
            try{
                p.set_value(func(args...));
            } catch(...){
                p.set_exception(std::current_exception());
            }
    });
    t.detach();
    return res;
}

int main(int argc, char* argv[]) {  
    // 加法例子
    auto fut = spawn_async([](int a, int b) {
        return a+b;
    }, 1, 2);
    
    // throw exception的例子
    auto fut1 = spawn_async([]() {
        throw std::runtime_error("Spawn async error!");
        return 1;
    });
    std::cout << "add 1 + 2 = " << fut.get() << std::endl;
    std::cout << "runtime_error: " << fut1.get() << "\n";
    return EXIT_SUCCESS;
}
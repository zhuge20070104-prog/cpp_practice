#include <iostream>
#include <list>
#include <algorithm>
#include <future>
#include <functional>

// 类似std::async的实现，使用std::packaged_task实现
template <typename Func, typename ...  Arg>
std::future<typename std::result_of<Func(Arg&&...)>::type> 
spawn_task(Func&& func, Arg && ... arg) {
    using result_type = typename  std::result_of<Func(Arg&&...)>::type;
    std::packaged_task<result_type(Arg&&...)> task(std::move(func));
    
    std::future<result_type> res(task.get_future());
    std::thread t(std::move(task), std::move(arg)...);
    t.detach();
    return res;
}

int sum(int a, int b) {
    return a + b;
}

int main(int argc, char* argv[]) {  
    auto fut = spawn_task(sum, 10, 10);
    std::cout << "future result: " << fut.get() << "\n";
    return EXIT_SUCCESS;
}
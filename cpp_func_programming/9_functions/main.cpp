#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <functional>

void demo_function() {
    std::cout << "Called demo_function" << std::endl;
}

void adder(int a, int b) {
    std::cout << "Called adder, a+b= " << a + b  << std::endl;
}

class functor {
public:
    void operator()() const { 
        std::cout << "Called functor"  << std::endl;
    }
};


int main(int argc, char* argv[]) {
    // push_back 几个函数到vector 容器，然后逐个调用
    std::vector<std::function<void()>> funcs;
    funcs.push_back(demo_function); 
    functor functor_inst;
    funcs.push_back(functor_inst);
    funcs.push_back([](){
        std::cout << "Called anonymous lambda" << std::endl;
    });
    funcs.push_back(std::bind(&adder, 10, 15));

    for(auto& f: funcs){
        f();
    }
      
    return EXIT_SUCCESS;
}

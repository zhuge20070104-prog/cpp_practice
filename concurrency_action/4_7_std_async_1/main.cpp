#include <iostream>
#include <mutex>
#include <thread>
#include <future>
#include <string>

struct X {
    void foo(int i, std::string const& s) {
        std::cout << "i: " << i << " s: " << s << std::endl;
    }

    std::string bar(std::string const& s) {
        std::string res = "bar:  ";
        res += s;
        return res;
    }
};

// std::async 对函数对象的支持 
struct Y {
    double operator()(double val) {
        std::cout << val << std::endl;
        return val;
    }
};

X baz(X& x) {
    std::cout << "Address of x: " << &x << std::endl;
}


// move only的 函数对象，空参数
class move_only {

public:
    move_only(){
    }

    move_only(move_only&&) {}
    
    move_only& operator=(move_only&&) {
        return *this;
    }

    move_only(move_only const&) = delete;
    move_only& operator=(move_only const&) = delete;

    void operator()() {
        std::cout << "move_only operator()()" << std::endl;
    }
};

int main(int argc, char* argv[]) {  
    X x;
    // 成员函数的用法
    // 这个hello 其实传了拷贝，需要用std::cref(lvalue) 才能传原值的常量引用
    auto f1 = std::async(&X::foo, &x, 42, "hello");
    auto f2 = std::async(&X::bar, x, "goodbye");
    f1.wait();
    std::cout  << "bar result: " << f2.get() << std::endl;

    // 函数对象的用法
    Y y;
    auto f3 = std::async(Y(), 3.141);
    auto f4 = std::async(std::ref(y), 2.718);
    // 全局对象的用法
    std::cout <<"main x address: " << &x << std::endl;
    auto f6 = std::async(baz, std::ref(x));
    f3.get();
    f4.get();
    f6.get();

    // move_only的函数对象，空参数
    auto f5 = std::async(move_only());
    f5.wait();

    return EXIT_SUCCESS;
}
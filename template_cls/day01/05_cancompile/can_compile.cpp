#include <iostream>

class A {
public:
    void func() {
        std::cout << "A::func" << std::endl;
    }
};

template <typename T>
void foo() {
    A a;
    // 已知类型调用
    a.func();
    T t;
    // 未知类型调用
    t.func();
}

int main(int argc, char* argv[]) {
    foo<A>();
    return EXIT_SUCCESS;
}
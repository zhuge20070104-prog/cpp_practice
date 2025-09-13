#include <iostream>

class A {
public:
    class B {
    public:
        void foo() {
            std::cout << "A::B::foo()" << std::endl; 
        }
    };
};

template <class T>
void Func() {
    typename T::B b;
    b.foo();
}

int main(int argc, char* argv[]) {
    Func<A>();
    return EXIT_SUCCESS;
}
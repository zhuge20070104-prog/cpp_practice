#include <iostream>

template <class T>
class Base {
public:
    virtual void foo() {
        std::cout << "Base<T>::foo()" << std::endl;
    }
};

template <class T, class D>
class Derived: public Base<T> {
public:
    void foo() {
        std::cout << "Derived<T, D>::foo()" << std::endl;
    }

    // Template 不能virtual
    // template <class M> 
    // virtual void bar() {
    //     std::cout << "Derived<T, D>::bar()" << std::endl;
    // }
};


int main(int argc, char* argv[]) {
    Derived<int, int> d;
    Base<int>* pBase = &d;
    pBase->foo();
    return EXIT_SUCCESS;
}
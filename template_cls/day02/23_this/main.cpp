#include <iostream>

template <class T>
class Base {
public:
    int m_i;
    void foo() {
        std::cout << "Base<T>::foo()" << std::endl;
    }
};

template <class T, class D>
class Derived: public Base<T> {
public:
    void bar() {
        Base<T>::m_i = 5;
        this->foo();
    }
};


int main(int argc, char* argv[]) {
    Derived<int, double> d;
    d.bar();
    return EXIT_SUCCESS;
}
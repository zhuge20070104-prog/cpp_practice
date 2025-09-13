#include <iostream>

class A {
public:
    template <class T>
    void foo() {
        std::cout << "A::foo<T>()" << std::endl;
    }
};

template <class D>
void Func() {
    D d;
    d. template foo<int>();
}

int main(int argc, char* argv[]) {
    Func<A>();
    return EXIT_SUCCESS;
}
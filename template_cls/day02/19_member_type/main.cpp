#include <iostream>
#include <string>

template <class X>
class A {
public:
    template <class Y>
    class B {
    public:

        template <class Z>
        class C {
        public:
            template <class T>
            void foo();
        };
    };
};

template <class X>
template <class Y>
template <class Z>
template <class T>
void A<X>::B<Y>::C<Z>::foo() {
    std::cout << "A<X>::B<Y>::C<Z>::foo<T>()" << std::endl;
}

int main(int argc, char* argv[]) {
    A<int>::B<double>::C<float> c;
    c.foo<std::string>();
    return EXIT_SUCCESS;
}
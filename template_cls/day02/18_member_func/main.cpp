#include <iostream>


template <class T>
class CMath{
public:
    template <class D>
    void foo();
};


template <class T>
template <class D>
void CMath<T>::foo() {
    std::cout << "CMath<T>::foo<D>()" << std::endl;
}

int main(int argc, char* argv[]) {
    CMath<int> m;
    m.foo<double>();
    return EXIT_SUCCESS;
}
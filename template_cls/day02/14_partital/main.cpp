#include <iostream>

template <class T, class D>
class CMath {
public:
    static void foo() {
        std::cout << "1: CMath<T, D>::foo()" << std::endl;
    }
};

// 局部特化
template <class T>
class CMath<T, short> {
public:
    static void foo() {
        std::cout << "2: CMath<T, short>::foo()" << std::endl;
    }
};

template <class T>
class CMath<T, T> {
public:
    static void foo() {
        std::cout << "3: CMath<T, T>::foo()" << std::endl;
    }
};

template <class T, class D>
class CMath<T*, D*> {
public:
    static void foo() {
        std::cout << "4: CMath<T*, D*>::foo()" << std::endl;
    }
};

int main(int argc, char* argv[]) {
    CMath<int, double>::foo(); // 1
    CMath<int, short>::foo(); // 2
    CMath<int*, double*>::foo(); // 4


    return EXIT_SUCCESS;
}
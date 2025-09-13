#include <iostream>

template <typename T>
class A {
public:
    static void print() {
        std::cout << "&m_i" << &m_i << " &m_t:" << &m_t << std::endl; 
    }

private:
    static int m_i;
    static T m_t;
};

template <typename T>
int A<T>::m_i = 0;

template <typename T>
T A<T>::m_t = T();

int main(int argc, char* argv[]) {
    A<int> x, y, z;
    // 静态对象不算入类实例的大小
    std::cout << "size of A<int>: " << sizeof(x)  << std::endl;
    x.print();
    y.print();
    z.print();
    A<int>::print();

    A<double> m, n, t;    
    std::cout << "size of A<double>: " << sizeof(m)  << std::endl;
    m.print();
    n.print();
    t.print();
    A<double>::print();
    
    return EXIT_SUCCESS;
}
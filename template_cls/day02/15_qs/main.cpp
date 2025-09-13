#include <iostream>
#include <typeinfo>

template <class T=short, class D=int>
class CMath {
public:
    void print() {
        std::cout << "m_t: " << typeid(m_t).name() << " "
            << "m_d: " << typeid(m_d).name() << std::endl;
    }
private:
    T m_t;
    D m_d;
};

int main(int argc, char* argv[]) {
    CMath<float, double> m;
    m.print();

    CMath<> m2;
    m2.print();
    return EXIT_SUCCESS;
}
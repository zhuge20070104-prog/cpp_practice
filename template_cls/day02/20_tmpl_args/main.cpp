#include <iostream>

template <class T>
class Array {
public:
    T& operator[] (std::size_t i) {
        return m_arr[i];
    }
private:
    T m_arr[10];
};


template <class D, template<class M>class C>
class Sum {
public:
    Sum(C<D>& s): m_s(s) {}

    D add() {
        D d = 0;
        for(int i=0; i<10; ++i) {
            d += m_s[i];
        }
        return d;
    }
private:
    C<D> m_s;
};


int main(int argc, char* argv[]) {
    Array<int> a;
    for(int i=0; i<10; ++i) {
        a[i] = i+1;
    }

    Sum<int, Array> s(a);
    std::cout << s.add() << std::endl;
    
    return EXIT_SUCCESS;
}
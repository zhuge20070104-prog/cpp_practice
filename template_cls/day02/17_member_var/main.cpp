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

template <class D>
class Sum { // Sumer
public:
    Sum(Array<D>& s): m_s(s) {}
    
    D add() { // Get the sum value
        D d = 0;
        for(int i=0; i<10; ++i) {
            d += m_s[i];
        }
        return d;
    }
private:
    Array<D> m_s;
};


int main(int argc, char* argv[]) {
    Array<int> a;
    for(int i=0; i<10; ++i) {
        a[i] = i+1;
    }

    Sum<int> s(a);
    std::cout << s.add() << std::endl;
    return EXIT_SUCCESS;
}
#include <iostream>


template <class T, std::size_t S=15>
class Array {
public:
    T& operator[](std::size_t i) {
        return m_arr[i];
    }

    std::size_t size() {
        return S;
    }
private:
    T m_arr[S];
};


int main(int argc, char* argv[]) {
    Array<int> a;
    for(int i=0; i<a.size(); ++i) {
        a[i] = i+1;
    }

    for(int i=0; i<a.size(); ++i) {
        std::cout << a[i] << ' ';
    }
    std::cout << std::endl;
}
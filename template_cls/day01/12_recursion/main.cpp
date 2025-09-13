#include <iostream>

template <typename T>
class Array {
public:
    T& operator[](std::size_t i) {
        return m_i[i];
    }
private:
    T m_i[10];
};

int main(int argc, char* argv[]) {
    Array<Array<int>> m;
    for(int i=0; i<10; ++i) {
        for(int j=0; j<10; ++j) {
            m[i][j] = i+j;
        }
    }

    for(int i=0; i<10; ++i) {
        for(int j=0; j<10; ++j) {
            std::cout << m[i][j] << " ";
        }
        std::cout << std::endl;
    }
    return EXIT_SUCCESS;
}
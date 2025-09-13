#include <iostream>

class Integer {
public:
    Integer():m_i(0) {}
private:
    int m_i;
    friend std::ostream& operator<<(std::ostream& os, Integer const& that);    
};

std::ostream& operator<<(std::ostream& os, Integer const& that) {
    return os << that.m_i;
}

template <class T>
void Func() {
    // 零值初始化的两种写法
    // T t = T();
    T t();
    std::cout << "t=" << t << std::endl;
}

int main(int argc, char* argv[]) {
    Func<int>();
    Func<Integer>();
    return EXIT_SUCCESS;
}
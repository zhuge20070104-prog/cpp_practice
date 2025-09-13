#include <iostream>

class Integer {
public:
    Integer(int i):m_i(i) {}
    Integer operator+(Integer const& that) const {
        return m_i + that.m_i;
    }

    friend std::ostream& operator << (std::ostream& os, Integer const& in) {
        os << in.m_i;
        return os;
    }
private:
    int m_i;
};

template <typename T>
class CMath {
public:
    CMath(T const& t1, T const& t2):m_t1(t1), m_t2(t2) {}
    T add() {
        return m_t1 + m_t2;
    }
private:
    T m_t1;
    T m_t2;
};

int main(int argc, char* argv[]) {
    Integer ix = 100, iy = 200;
    CMath<Integer> m2(ix, iy);
    std::cout << "Two Integers add: " << m2.add() << std::endl;

    int nx = 10, ny = 20;
    CMath<int> m3(nx, ny);
    std::cout << "Two ints add: " << m3.add() << std::endl;
    return EXIT_SUCCESS;
}
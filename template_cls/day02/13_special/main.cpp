#include <iostream>
#include <cstring>
#include <string>

template <typename T>
class CMath {
public:
    CMath(T const& t1, T const& t2): m_t1(t1), m_t2(t2) {
    }

    T add() {
        return m_t1 + m_t2;
    }
private:
    T m_t1;
    T m_t2;
};

// 成员特化
template <>
char* const CMath<char* const>::add() {
    return strcat(m_t1, m_t2); 
}

int main(int argc, char* argv[]) {
    int nx=10, ny=20;
    CMath<int> m1(nx, ny);
    std::cout << m1.add() << std::endl;

    double dx=12.3, dy=45.6;
    CMath<double> m2(dx, dy);
    std::cout << m2.add() << std::endl;

    std::string sx="hello", sy=" world";
    CMath<std::string> m3(sx, sy);
    std::cout << m3.add() << std::endl;

    char cx[256]="hello", cy[256]=" world";
    CMath<char* const> m4(cx, cy);
    std::cout << m4.add() << std::endl;

    return EXIT_SUCCESS;
}
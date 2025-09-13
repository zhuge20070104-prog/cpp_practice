#include <iostream>

class Integer {
public:
    Integer(int i): m_i(i) {}

    bool operator>(Integer const& that) const {
        return m_i > that.m_i;
    }
private:
    int m_i;
};

template <typename T>
T Max(T x, T y) {
    return x>y ? x: y;
}

int main(int argc, char* argv[]) {
    Integer ix{100}, iy{200};
    Max<Integer>(ix, iy);

    int nx{10}, ny{20};
    std::cout << Max<int>(nx, ny) << std::endl;
    double dx=12.3, dy=45.6;
    std::cout << Max<double>(dx, dy) << std::endl;
    std::string sx="world", sy="hello";
    std::cout << Max<std::string>(sx, sy) << std::endl; 
    return EXIT_SUCCESS;
}
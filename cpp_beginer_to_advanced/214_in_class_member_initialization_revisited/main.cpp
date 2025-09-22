#include <iostream>

class Integer {
    int m_int;
public:
    explicit Integer(int i): m_int {i} {}

    Integer() = default;
    ~Integer() = default;
    
    int get_value() const {
        return m_int;
    }

    void set_value(int i) {
        m_int = i;
    }
};


class Point {
    double m_x;
    double m_y;
    Integer m_i;

public:
    Point() {}
    Point(double x, double y): m_x {x}, m_y {y} {}

    ~Point() = default;

    void print_info() const {
        std::cout << m_x << ", " << m_y << '\n';
        std::cout << m_i.get_value() << '\n';
    }
};

int main(int argc, char* argv[]) {
    // Junk data in p1
    Point p1;
    p1.print_info();
    return EXIT_SUCCESS;
}


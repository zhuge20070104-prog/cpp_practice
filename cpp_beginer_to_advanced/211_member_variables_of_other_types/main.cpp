#include <iostream>

class Integer {
public:
    explicit Integer(int value): inner_int{value} {}

    Integer() = default;
    ~Integer() = default;

    int get_value() const {
        return inner_int;
    }

    void set_value(int value) {
        inner_int = value;
    }
    
    
private:
    int inner_int{0};
};


class Point {
    double m_x{};
    double m_y{};

public:
    Integer i1 {0};
    const Integer i2 {2};
    static inline Integer i3 {3};
    static inline const Integer i4 {4};

    Integer* p_i5 {nullptr};

    static Integer i6;
    static const Integer i7;

    Point(double x, double y): m_x{x}, m_y{y}, p_i5 {new Integer{5}} {

    }
};

Integer Point::i6 {6};
const Integer Point::i7 {7};


int main(int argc, char* argv[]) {
    Point p {2.1, 3.6};

    std::cout << p.i1.get_value() << '\n';
    std::cout << p.p_i5->get_value() << '\n';
    return EXIT_SUCCESS;
}


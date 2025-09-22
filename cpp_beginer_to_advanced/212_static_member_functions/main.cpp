#include <iostream>

class Point {
public:
    Point(double x=0.0, double y=0.0): m_x(x), m_y(y) {
        ++m_count;
    }

    // static member function
    static std::size_t point_count() {
        return m_count;
    }

    static void print_point(const Point& p) {
        std::cout << p.m_x << ", " << p.m_y << '\n';
    }

private:
    double m_x {};
    double m_y {};
    static inline std::size_t m_count {0};

};

int main(int argc, char* argv[]) {
    std::cout << Point::point_count() << '\n';
    
    Point p1;
    std::cout << Point::point_count() << '\n';

    return EXIT_SUCCESS;
}


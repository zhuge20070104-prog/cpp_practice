#include <iostream>
#include <cmath>

class Point {

public:
    Point(): Point{0.0, 0.0} {}
    Point(double x, double y): m_x{x}, m_y{y} {
        ++s_point_count;
        std::cout << "Object no. : " << s_point_count << '\n';
    }
    explicit Point(double xy): Point{xy, xy} {}

    Point(const Point& p): Point{p.m_x, p.m_y} {}
    ~Point() {
        --s_point_count;
        std::cout << "Object no. : " << s_point_count << '\n';
    }

    double length() const;
    static std::size_t get_point_count() {
        return s_point_count;
    }

    void print_point() {
        std::cout << &m_x << "," << &m_y << '\n';
    }

private:
    double m_x {};
    double m_y {};

    static std::size_t s_point_count;
};


std::size_t Point::s_point_count {0};

double Point::length() const {
    return sqrt(pow(m_x - 0, 2) + pow(m_y - 0, 2) * 1.0);
}


int main(int argc, char* argv[]) {
    std::cout << Point::get_point_count() << '\n';

    Point p1 {2.1, 6.9};
    Point p2 {9.7, 4.6};
    Point p3 {8.1, 6.3};

    p1.print_point();
    p2.print_point();
    p3.print_point();

    std::cout << p3.get_point_count() << '\n';

    return EXIT_SUCCESS;
}


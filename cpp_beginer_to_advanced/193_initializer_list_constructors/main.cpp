#include <iostream>
#include <initializer_list>
#include <cassert>


struct Point {

public:
    Point(std::initializer_list<double> list) {
        std::cout << "Point(std::initializer_list<double> list)" << std::endl;
        assert(list.size() == 2);
        m_x = *(list.begin());
        m_y = *(list.begin() + 1);
    }

    void print_point() const {
        std::cout << "x: " << m_x << ", y: " << m_y << std::endl;
    }

private:
    double m_x {};
    double m_y {};
};


int main(int argc, char* argv[]) {
    Point p1 {2.6, 8.9};
    p1.print_point();
    return EXIT_SUCCESS;
}


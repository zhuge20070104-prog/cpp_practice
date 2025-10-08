#include <iostream>
#include "stream_insertable.h"


class Point: public StreamInsertable {
public:
    Point() = default;
    Point(double x, double y): m_x(x), m_y(y) {}

    virtual void stream_insert(std::ostream& os) const override {
        os << "Point{" << m_x << ", " << m_y << "}\n";
    }
private:
    double m_x {};
    double m_y {};
};

int main(int argc, char* argv[]) {
    Point point {2, 3};
    std::cout << point;
    return EXIT_SUCCESS;
}
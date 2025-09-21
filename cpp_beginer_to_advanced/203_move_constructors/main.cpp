#include <iostream>

class Point {
    double* m_px;
    double* m_py;

    void invalidate() {
        m_px = nullptr;
        m_py = nullptr;
    }

public:
    Point(double x, double y): m_px(new double(x)), m_py(new double(y)) {}

    ~Point() {
        delete m_px;
        delete m_py;
    }

    Point(const Point& src_point);
    Point(Point&& src_point) noexcept;

    void set_x(double x) {
        *m_px = x;
    }

    void set_y(double y) {
        *m_py = y;
    }

    double* get_x() const {
        return m_px;
    }

    double* get_y() const {
        return m_py;
    }

    void print_point() const {
        std::cout << "x: " << *m_px << ", y: " << *m_py << '\n';
    }
};


// Deep copy
Point::Point(const Point& src_point): 
m_px(new double(*(src_point.get_x()))), m_py(new double(*(src_point.get_y()))) 
{
    std::cout << "Copy constructor called\n";
}

Point::Point(Point&& src_point) noexcept:
        m_px(src_point.get_x()), m_py(src_point.get_y()) {
    src_point.invalidate();
    std::cout << "Move constructor called\n";
}


int main(int argc, char* argv[]) {
   
    Point p1 {1.6, 6.2};
    p1.print_point();

    Point p3 {std::move(Point{8, 10})};
    p3.print_point();
    
    return EXIT_SUCCESS;
}


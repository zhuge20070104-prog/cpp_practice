#ifndef _FREDRIC_POINT_H_
#define _FREDRIC_POINT_H_

class Number;
class Car;

#include <iostream>
#include <cassert>


class Point {
public:
    Point() = default;

    Point(double x, double y, int data);
    Point(const Number& num);
    void print_info() const {
        std::cout << m_x << ", " << m_y << '\n';
    }

    ~Point();

    double& operator[](std::size_t index) {
        assert((index==0) || (index==1));
        return (index==0) ? m_x: m_y;
    }

    friend Point operator+(const Point& left, const Point& right);

    // << as a member function
    // left operand will be the point class and right will be the ostream class - awkward
    std::ostream& operator<<(std::ostream& os) const {
        os << "Point: [" << m_x << ',' << m_y << ']' << '\n';
        std::cout << "Member operator << called\n";
        return os;
    }

    Point(const Point& right) {
        if(this!=&right) {
            delete point_data;
            point_data = new int {*(right.point_data)};
            m_x = right.m_x;
            m_y = right.m_y;
        }
        std::cout << "Copy constructor called\n";
    }


    Point operator=(const Point& right) {
        if(this!=&right) {
            delete point_data;
            m_x = right.m_x;
            m_y = right.m_y;
            point_data = new int{*(right.point_data)};
        }
        std::cout << "Copy assignment for Point called\n";
        return *this;
    }

    friend Point& operator+=(Point& left, const Point& right);
    friend Point& operator-=(Point& left, const Point& right);

    friend std::ostream& operator<<(std::ostream& out, const Point& p);
    friend std::istream& operator>>(std::istream& is, Point& p);

    void operator++() {
        ++m_x;
        ++m_y;
    }

    // int - necessary to differentiate the postfix from prefix
    // postfix ++ as a member
    // returned type can be set according to the need
    Point operator++(int) {
        Point local_point{*this};
        ++(*this);
        return local_point;
    }

    void operator--() {
        --m_x;
        --m_y;
    }

    Point operator--(int) {
        Point local_point{*this};
        --(*this);
        return local_point;
    }

    // copy a Car object to Point
    // void - chained assignments are not supported
    void operator=(const Car& right_car);
    void operator=(const Number& n);

private:
    double m_x;
    double m_y;
    int* point_data{nullptr};
};


inline Point operator+(const Point& left, const Point& right) {
    Point p {left};
    return p += right;
}

inline Point& operator+=(Point& left, const Point& right) {
    left.m_x += right.m_x;
    left.m_y += right.m_y;
    return left;
}

inline Point& operator-=(Point& left, const Point& right) {
    left.m_x -= right.m_x;
    left.m_y -= right.m_y;
    return left;
}

inline std::ostream& operator<<(std::ostream& os, const Point& p) {
    os << "Point: [" << p.m_x << ", " << p.m_y << ", " << *(p.point_data) << "]";
    return os;
} 

inline std::istream& operator>>(std::istream& is, Point& p) {
    std::cout << "Enter the x coordinate: ";
    is >> p.m_x;
    std::cout << "Enter the y coordinate: ";
    is >> p.m_y;

    return is;
}

#endif
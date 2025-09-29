#include <iostream>
#include <cmath>


class Point {
public:
    Point(int x, int y): m_x{x}, m_y{y} {}
    bool operator==(const Point& other) const {
        return length() == other.length();
    }

    std::partial_ordering operator<=>(const Point& other) const {
        if(is_within_bounds(other) && is_within_bounds(*this)) {
          if(length() > other.length()) {
            return std::partial_ordering::greater;
          } else if(length() < other.length()) {
            return std::partial_ordering::less;
          } else {
            return std::partial_ordering::equivalent;
          }
        } 

        return std::partial_ordering::unordered;
    }

private:
    int m_x {};
    int m_y {};

    double length() const {
        return std::sqrt(pow(m_x - 0, 2) + pow(m_y - 0, 2) * 1.0);
    }

    bool is_within_bounds(const Point& p) const {
        if((std::abs(p.m_x) < 100) && (std::abs(p.m_y) < 100)) {
            return true;
        }
        return false;
    }
};


int main(int argc, char* argv[]) {

    Point p1 {11, 98};
    Point p2 {88, 72};

    std::cout << "p1 == p2: " << (p1 == p2) << "\n";
    std::cout << "p1 < p2: " << (p1 < p2) << "\n";
    std::cout << "p1 > p2: " << (p1 > p2) << "\n";
    std::cout << "p1!= p2: " << (p1 != p2) << "\n";

    return EXIT_SUCCESS;
}
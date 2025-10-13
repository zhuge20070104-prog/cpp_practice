#include <exception>
#include <iostream>
#include <string>
#include <string_view>
#include <concepts>
#include <vector>

template <typename T>
concept OutputStreamable = requires(std::ostream& o, T d) {
    o << d;
};

template <OutputStreamable T>
std::ostream& operator<<(std::ostream& o, const std::vector<T>& d) {
    for(const auto& item : d) {
        o << item << " ";
    }
    return o;
}

struct Point {
    double m_x {};
    double m_y {};

    Point() = default;
    Point(double x, double y): m_x{x}, m_y{y} {}

    friend std::ostream& operator<<(std::ostream& o, const Point& p) {
        o << "Point: [" << p.m_x << ", " << p.m_y << "]";
        return o;
    }
};

template <typename T>
concept Number = (std::integral<T> || std::floating_point<T>)
    && (!std::same_as<T, char> && !std::same_as<T, bool>);

template <Number T, Number U>
auto add(T a, U b) {
    return a + b;
}

int main(int argc, char* argv[]) {
    std::vector<int> numbers {1, 2, 3, 4, 5};
    std::cout << numbers << std::endl;

    std::vector<Point> points {{1.0, 2.0}, {3.0, 4.0}};
    std::cout << points << std::endl;

    std::cout << add(1, 2.2) << std::endl;
    // std::cout << add(true, false) << std::endl;
    return EXIT_SUCCESS;
}

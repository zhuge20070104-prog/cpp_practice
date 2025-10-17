#include <exception>
#include <iostream>
#include <string>
#include <string_view>

class Item {
public:
    Item(int a, int b): m_a {a}, m_b {b} {}

    void print_members() {
        auto lambda {[this] () {
            std::cout << "m_a: " << m_a << ", m_b: " << m_b << '\n';
        }};
        lambda();
    }
private:
    int m_a {};
    int m_b {};
};

int main(int argc, char* argv[]) {
    Item item1 {2, 2};
    item1.print_members();
    return EXIT_SUCCESS;
}

#include <iostream>
#include <string>
#include <string_view>
#include <exception>


class DivideByZero: public std::exception {

public:
    DivideByZero(int a, int b): std::exception{}, m_a{a}, m_b{b} {}

    virtual const char* what() const noexcept override {
        return (std::string {"Division by zero detected: "} +
            std::to_string(m_a) + " / " + std::to_string(m_b)).c_str();
    }

    int get_a() const {
        return m_a;
    }

    int get_b() const {
        return m_b;
    }
private:
    int m_a {};
    int m_b {}; 
};

int divide(int a, int b) {
    if(b == 0) {
        throw DivideByZero(a, b);
    }
    return a/b;
}

int main(int argc, char* argv[]) {
    try {
        divide(2, 0);
    } catch(std::exception& ex) {
        DivideByZero* ptr_dzero = dynamic_cast<DivideByZero*>(&ex);
        if(ptr_dzero) {
            std::cout << ex.what() << ", dividing a: " << ptr_dzero->get_a() 
            << " by b: " << ptr_dzero->get_b() << std::endl;
        }
        std::cout << ex.what() << std::endl;
    }
    return EXIT_SUCCESS;
}
#include <exception>
#include <iostream>

template <typename T>
class TemplateClass;

template <typename T>
void some_func(const TemplateClass<T>&);


template <typename T>
class TemplateClass {
    friend void some_func<T>(const TemplateClass<T>&);
public:
    explicit TemplateClass() = default;
    void setup(const T& param) {
        m_var = param;
    }

    void do_something(T a, T b) {
        std::cout << a << ", " << b << '\n';
    }

private:
    T m_var{};
};

template <typename T>
void some_func(const TemplateClass<T>& obj) {
    std::cout << "friend accessing the private stuff of TemplateClass: ";
    std::cout << obj.m_var << '\n';
}


int main(int argc, char* argv[]) {
    TemplateClass<int> tc1;
    tc1.setup(2);
    some_func(tc1);

    TemplateClass<double> tc2;
    tc2.setup(8.8);
    some_func(tc2);
    
    return EXIT_SUCCESS;
}

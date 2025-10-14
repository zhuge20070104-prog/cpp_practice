#include <iostream>
#include <cstring>

template <typename T>
class Adder {
public:
    Adder() = default;
    T add(T a, T b);
    void do_something() {
        std::cout << "Doing something\n";
    }
};

template <typename T>
T Adder<T>::add(T a, T b) {
    std::cout << "Using add() from a regular template instance\n";
    return a + b;
}


template <>
class Adder<char*> {
public:
    Adder() = default;
    char* add(char* a, char* b);
};


char* Adder<char*>::add(char* a, char* b) {
    std::cout << "Using add() from a specialization template instance\n";
    return strcat(a, b);
}

int main(int argc, char* argv[]) {
    Adder<int> int_adder;
    int_adder.do_something();
    std::cout << "int_adder.add(1, 2): " << int_adder.add(1, 2) << std::endl;

    char c1[] {"hello"};
    char c2[] {"world"};

    Adder<char*> char_adder;
    std::cout << "char_adder.add(c1, c2): " << char_adder.add(c1, c2) << std::endl;

    return EXIT_SUCCESS;
}

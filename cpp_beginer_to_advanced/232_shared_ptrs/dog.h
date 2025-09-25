#ifndef _FREDRIC_DOG_H_
#define _FREDRIC_DOG_H_

#include <iostream>
#include <string>


class Dog {
public:
    explicit Dog(const std::string& name);
    Dog() = default;
    ~Dog();

    void print_dog() const {
        std::cout << "Dog: " << m_name << '\n';
    }

    std::string get_name() const {
        return m_name;
    }

    void set_name(const std::string& name) {
        m_name = name;
    }

private:
    std::string m_name {"Elliot"};
};

#endif
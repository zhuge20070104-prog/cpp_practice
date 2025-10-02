#ifndef _FREDRIC_PERSON_H
#define _FREDRIC_PERSON_H

#include <iostream>
#include <string>
#include <string_view>


class Person {
    friend std::ostream& operator<<(std::ostream& os, const Person& person);

public:
    Person() {
        std::cout << "Default Person contructor called\n";
    }

    Person(std::string_view fullname, int age, std::string_view address);

    ~Person() {
        std::cout << "Person destructor called\n";
    }

    std::string get_fullname() const {
        return m_fullname;
    }

    int get_age() const {
        return m_age;
    }

    std::string get_address() const {
        return m_address;
    }

public:
    std::string m_fullname {"None"};

protected:
    int m_age {};

private:
    std::string m_address {"None"};
};

#endif
#ifndef _FREDRIC_PERSON_H
#define _FREDRIC_PERSON_H

#include <iostream>
#include <string>
#include <string_view>

class Person {
    friend std::ostream& operator<<(std::ostream& os, const Person& person);

public:
    Person() = default;
    Person(std::string_view fullname, int age, std::string_view address);
    ~Person() = default;

    std::string get_fullname() const {
        return m_fullname;
    }

    int get_age() const {
        return m_age;
    }

    std::string get_address() const {
        return m_address;
    }

    int add(int a, int b) {
        return a + b;
    }

    int add(int a, int b, int c) {
        return a + b + c;
    }

public:
    std::string m_fullname {"Fredric Zhu"};

protected:
    int m_age {32};

private:
    std::string m_address {"Wuhan, China"};
};

#endif
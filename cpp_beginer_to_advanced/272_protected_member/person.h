#ifndef _FREDRIC_PERSON_H
#define _FREDRIC_PERSON_H

#include <iostream>
#include <string>
#include <string_view>

class Person {
    friend std::ostream& operator<<(std::ostream& os, const Person& person);

public:
    Person() = default;
    Person(std::string_view fname, std::string_view lname);
    ~Person() = default;

protected:
    std::string m_fname{};
    std::string m_lname{};
};

#endif
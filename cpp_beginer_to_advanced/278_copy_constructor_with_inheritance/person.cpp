#include "person.h"


std::ostream& operator<<(std::ostream& os, const Person& person) {
    os << person.get_fullname() << ", " << person.get_age() << ", " << person.get_address();
    return os;
}

Person::Person(const Person& other):
    m_fullname{other.m_fullname}, m_age{other.m_age}, m_address{other.m_address} {
}

Person::Person(std::string_view fullname, int age, std::string_view address):
    m_fullname{fullname}, m_age{age}, m_address{address} {
    std::cout << "Custom copy constructor called for Person\n";
}

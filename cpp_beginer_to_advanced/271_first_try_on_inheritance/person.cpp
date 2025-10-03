#include "person.h"


std::ostream& operator<<(std::ostream& os, const Person& person) {
    os << person.get_fname() << " " << person.get_lname();
    return os;
}

Person::Person(std::string_view fname, std::string_view lname):
    m_fname{fname}, m_lname{lname} {
    std::cout << "Person constructor called\n";
}

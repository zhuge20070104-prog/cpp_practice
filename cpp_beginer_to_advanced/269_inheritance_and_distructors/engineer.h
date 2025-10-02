#ifndef _FREDRIC_ENGINEER_H
#define _FREDRIC_ENGINEER_H

#include "person.h"

class Engineer: public Person {
    friend std::ostream& operator<<(std::ostream& os, const Engineer& engineer);

public:
    Engineer(std::string_view fullname, int age, std::string_view address, int contact_count);

    // inheriting the base constructor
    // this will generate a base like constructor in the engineer class
    // which will initialize the base portion only,
    // all person ctors will be inherited, whether default or custom
    // the actual construtor will be an engineer ctor but with base params only
    using Person::Person;


    ~Engineer() {
        std::cout << "Engineer is destroyed\n";
    }

    void build_something() {
        std::cout << m_fullname;
        std::cout << m_age;
    }

private:
    int m_contact_count {};
};

#endif
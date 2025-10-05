#ifndef _FREDRIC_ENGINEER_H
#define _FREDRIC_ENGINEER_H

#include "person.h"

class Engineer: private Person {
    friend std::ostream& operator<<(std::ostream& os, const Engineer& engineer);
public:
    Engineer() = default;
    Engineer(std::string_view fullname, int age, std::string_view address, int contact_count);
    ~Engineer() = default;

    using Person::Person;
    
    void build_something() {
        std::cout << m_fullname;
        std::cout << m_age;
    }

    
private:
    int m_contact_count {};
};
#endif
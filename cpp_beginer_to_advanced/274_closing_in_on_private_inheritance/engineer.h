#ifndef _FREDRIC_ENGINEER_H
#define _FREDRIC_ENGINEER_H

#include "person.h"

class Engineer: public Person {
    friend std::ostream& operator<<(std::ostream& os, const Engineer& engineer);
public:
    Engineer() = default;
    ~Engineer() = default;

    void build_something() {
        std::cout << m_fullname;
        std::cout << m_age;
    }

private:
    int contact_count {};
};
#endif
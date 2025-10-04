#ifndef _FREDRIC_NURSE_H
#define _FREDRIC_NURSE_H

#include "person.h"

class Nurse: public Person {
    friend std::ostream& operator<<(std::ostream& os, const Nurse& nurse);
public:
    Nurse() = default;
    ~Nurse() = default;

    void treat_well() {
        m_fullname = "Treated";
        std::cout << m_fullname << ", " << (m_age = 32) << ", " << (cert_id = 2353);
    }
private:
    int cert_id {};
};

#endif
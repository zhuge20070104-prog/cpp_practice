#ifndef _FREDRIC_CIVIL_ENGINEER_H
#define _FREDRIC_CIVIL_ENGINEER_H

#include "engineer.h"

class CivilEngineer: public Engineer {
    friend std::ostream& operator<<(std::ostream& os, const CivilEngineer& civil_engineer);
public:
    CivilEngineer() = default;
    CivilEngineer(std::string_view fullname, int age, std::string_view address, int contact_count, std::string_view specialilty);
    ~CivilEngineer() = default;

    void build_road();
private:
    std::string m_specialilty {"None"};
};

#endif
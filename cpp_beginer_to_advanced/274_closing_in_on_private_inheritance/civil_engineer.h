#ifndef _FREDRIC_CIVIL_ENGINEER_H
#define _FREDRIC_CIVIL_ENGINEER_H

#include "engineer.h"

class CivilEngineer: public Engineer {
    friend std::ostream& operator<<(std::ostream& os, const CivilEngineer& civil_engineer);
public:
    CivilEngineer() = default;
    ~CivilEngineer() = default;

    void build_road();
private:
    std::string m_specialilty {"None"};
};

#endif
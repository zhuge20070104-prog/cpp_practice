#include "civil_engineer.h"

std::ostream& operator<<(std::ostream& os, const CivilEngineer& civil_engineer) {
    os << civil_engineer.m_specialilty << ", " << civil_engineer.get_fullname() 
        << ", " << civil_engineer.get_age() << ", " << civil_engineer.get_address();
    return os;
}

void CivilEngineer::build_road() {
    std::cout << "Building road\n";
    std::cout << "add(2, 2):" << add(2, 2) << '\n';
    std::cout << "add(2, 2, 2):" << add(2, 2, 2) << '\n';
}
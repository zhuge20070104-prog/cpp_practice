#include "civil_engineer.h"

std::ostream& operator<<(std::ostream& os, const CivilEngineer& civil_engineer) {
    os << civil_engineer.m_specialilty;
    return os;
}

void CivilEngineer::build_road() {
    std::cout << "Building road\n";
}
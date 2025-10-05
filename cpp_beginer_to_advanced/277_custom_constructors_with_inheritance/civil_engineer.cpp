#include "civil_engineer.h"

std::ostream& operator<<(std::ostream& os, const CivilEngineer& civil_engineer) {
    os << civil_engineer.m_specialilty;
    return os;
}

CivilEngineer::CivilEngineer(std::string_view fullname, int age, std::string_view address, int contact_count, std::string_view specialilty):
    Engineer{fullname, age, address, contact_count}, m_specialilty{specialilty} {
    std::cout << "CivilEngineer received the data\n";
}

void CivilEngineer::build_road() {
    std::cout << "Building road\n";
}
#include "nurse.h"

std::ostream& operator<<(std::ostream& os, const Nurse& nurse) {
    os << nurse.get_fullname() << ", " << nurse.get_age();
    os << ", " << nurse.get_address() << ", " << nurse.cert_id;
    return os;
}
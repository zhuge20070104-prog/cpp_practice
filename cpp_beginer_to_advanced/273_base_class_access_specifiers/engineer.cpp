#include "engineer.h"

std::ostream& operator<<(std::ostream& os, const Engineer& engineer) {
    os << engineer.get_fullname() << ", " << engineer.get_age();
    os << ", " << engineer.get_address() << ", " << engineer.contact_count;
    return os;
}
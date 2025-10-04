#include "player.h"

std::ostream& operator<<(std::ostream& os, const Player& player) {
    os << player.get_fullname() << ", " << player.get_age();
    os << ", " << player.get_address();
    return os;
}
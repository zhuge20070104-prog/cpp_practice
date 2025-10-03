#include "player.h"

std::ostream& operator<<(std::ostream& os, const Player& player) {
    os << player.m_fname << " " << player.m_lname;
    os << ", Game: " << player.m_game;
    return os;
}

Player::Player(std::string_view game, std::string_view fname, std::string_view lname):
    m_game{game}{
    this->m_fname = fname;
    this->m_lname = lname;
}
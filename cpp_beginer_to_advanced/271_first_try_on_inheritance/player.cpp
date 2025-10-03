#include "player.h"

std::ostream& operator<<(std::ostream& os, const Player& player) {
    os << player.get_fname() << " " << player.get_lname();
    os << ", Game: " << player.m_game;
    return os;
}

Player::Player(std::string_view game):
    m_game{game} {
}
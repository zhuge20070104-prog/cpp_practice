#ifndef _FREDRIC_PLAYER_H
#define _FREDRIC_PLAYER_H

#include "person.h"
#include <string>

class Player: public Person {
    friend std::ostream& operator<<(std::ostream& os, const Player& player);
public:
    Player() = default;
    explicit Player(std::string_view game);
    ~Player() = default;
private:
    std::string m_game{};
};

#endif
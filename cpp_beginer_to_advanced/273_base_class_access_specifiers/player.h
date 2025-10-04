#ifndef _FREDRIC_PLAYER_H
#define _FREDRIC_PLAYER_H

#include "person.h"
#include <string>

class Player: public Person {
    friend std::ostream& operator<<(std::ostream& os, const Player& player);
public:
    Player() = default;
    ~Player() = default;
    void play() {
        m_fullname = "Somebody played with the name";
        m_age -= 2;
    }
    
private:
    int m_career_start_year {};
    double m_salary {};
    int m_health_factor {};
};

#endif
#ifndef _FREDRIC_ARRAY_BE_PROPERTY_HPP_
#define _FREDRIC_ARRAY_BE_PROPERTY_HPP_

#include "log.h"
#include <memory>
#include <string>
#include <array>
#include <numeric>
#include <iostream>


class Creature {
    // count 是array的大小，是个结束符
    enum Abilities {
        Strength,
        Agility,
        Intelligence,
        Count
    };

    std::array<int, Count> abilities;

public:
    int get_strength() {
        return abilities[Strength];
    }

    void set_strength(int val) {
        abilities[Strength] = val;
    }

    int get_aglity() {
        return abilities[Agility];
    }

    void set_aglity(int val) {
        abilities[Agility] = val;
    }

    int get_intelligence() {
        return abilities[Intelligence];
    }

    void set_intelligence(int val) {
        abilities[Intelligence] = val;
    }

    int sum() const {
        return std::accumulate(abilities.begin(), abilities.end(), 0);
    }

    double average() const {
        return sum()/(double) Count;
    }

    int max() const {
        return *std::max_element(abilities.begin(), abilities.end());
    }
};

#endif
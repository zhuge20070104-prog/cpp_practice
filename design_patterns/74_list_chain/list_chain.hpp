#ifndef _FREDRIC_LIST_CHAIN_HPP_
#define _FREDRIC_LIST_CHAIN_HPP_
#include <string>
#include <iostream>
#include <memory>
#include <functional>
#include <vector>

#include "log.h"

struct Creature {
    std::string name;
    int attack, defense;

    Creature(std::string const& name_, int attack_, int defense_):
        name(name_), attack(attack_), defense(defense_) {}
    
    friend std::ostream& operator<<(std::ostream& os, Creature const& c) {
        os << "name: " << c.name << " attack: " << c.attack << " defense: " << c.defense;
        return os;
    }
};

class CreatureModifier {
protected:
    Creature& creature;

public:
    CreatureModifier(Creature& creature_): 
        creature(creature_) {}
    
    virtual void handle() = 0;
};

class DoubleAttackModifier: public CreatureModifier {
public:
    DoubleAttackModifier(Creature& creature_):
        CreatureModifier(creature_) {}
    
    void handle() override {
        creature.attack *= 2;
    }
};

class IncreaseDefenseModifier: public CreatureModifier {
public:
    IncreaseDefenseModifier(Creature& creature_):
        CreatureModifier(creature_) {}
    
    void handle() override {
        if(creature.attack <= 2) {
            ++creature.defense;
        }
    }
};

class NoBonusesModifier: public CreatureModifier {
public:
    NoBonusesModifier(Creature& creature_):
        CreatureModifier(creature_){}
    
    // 啥都不干，用于断开链接
    void handle() override {}
};

struct CreatureModifierChain {
    std::vector<CreatureModifier*> modifiers{};

    void add(CreatureModifier* modifier) {
        modifiers.emplace_back(std::move(modifier));
    }

    void handle() {
        for(auto const& modifier: modifiers) {
            if(typeid(*modifier) == typeid(NoBonusesModifier)) {
                break;
            } else {
                modifier->handle();
            }
        }
    }
};

#endif
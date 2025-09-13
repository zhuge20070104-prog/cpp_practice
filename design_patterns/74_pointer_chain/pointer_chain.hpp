#ifndef _FREDRIC_POINTER_CHAIN_HPP_
#define _FREDRIC_POINTER_CHAIN_HPP_
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
    CreatureModifier* next {nullptr};
protected:
    Creature& creature;
    
public:
    CreatureModifier(Creature& creature_): 
        creature(creature_) {}
    
    // 这不是虚函数，因为不是直接调用子类的方法，待会子类要调用父类的方法连接链条
    void add(CreatureModifier* cm) {
        if(next) next->add(cm);
        else next = cm;
    }

    // 直接调用next的handle 方法，接起链条
    virtual void handle() {
        if(next) next->handle();
    }
};

class DoubleAttackModifier: public CreatureModifier {
public:
    DoubleAttackModifier(Creature& creature_):
        CreatureModifier(creature_) {}
    
    void handle() override {
        creature.attack *= 2;
        CreatureModifier::handle();
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
        CreatureModifier::handle();
    }
};

class NoBonusesModifier: public CreatureModifier {
public:
    NoBonusesModifier(Creature& creature_):
        CreatureModifier(creature_){}
    
    // 啥都不干，用于断开链接
    void handle() override {}
};

#endif
#ifndef _FREDRIC_MULTI_METHODS_HPP_
#define _FREDRIC_MULTI_METHODS_HPP_

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <typeinfo>
#include <typeindex>
#include <sstream>
#include <map>
#include <functional>

using type_index = std::type_index;

struct GameObject;

// 全局函数，两种类型的对象相遇
void collide(GameObject& first, GameObject& second);

struct GameObject {
    virtual ~GameObject() = default;
    virtual type_index type() const = 0;
    
    virtual void collide(GameObject& other) {
        // 调用全局的撞击函数
        ::collide(*this, other);
    }
};

// 使用CRTP来获取对象的类型
template <typename T>
struct GameObjectImpl: public GameObject {
    type_index type() const override {
        return typeid(T);
    }
};

struct Planet: public GameObjectImpl<Planet> {};
struct Asteroid: public GameObjectImpl<Asteroid> {};
struct Spaceship: public GameObjectImpl<Spaceship> {};
struct ArmedSpaceship: Spaceship {
    type_index type() const override {
        return typeid(ArmedSpaceship);
    }
};


// 宇宙飞船在行星上着陆
void spaceship_planet() {
    std::cout << "Spaceship lands on planet\n";
}

// 小行星在大气中燃烧
void asteroid_planet() {
    std::cout << "Asteroid burns up in atomosphere\n";
}

// 小行星撞上宇宙飞船
void asteroid_spaceship() {
    std::cout << "Asteroid hits and destroys spaceship\n";
}

// 宇宙飞船射击小行星
void asteroid_armed_spaceship() {
    std::cout << "Spaceship shoots asteroid\n";
}

std::map<std::pair<type_index, type_index>, void(*)(void)> outcomes {
    {{typeid(Spaceship), typeid(Planet)}, spaceship_planet}, 
    {{typeid(Asteroid), typeid(Planet)}, asteroid_planet},
    {{typeid(Asteroid), typeid(Spaceship)}, asteroid_spaceship},
    {{typeid(Asteroid), typeid(ArmedSpaceship)}, asteroid_armed_spaceship}
};

void collide(GameObject& first, GameObject& second) {
    auto it = outcomes.find({first.type(), second.type()});
    if(it == outcomes.end()) {
        it = outcomes.find({second.type(), first.type()});
        if(it == outcomes.end()) {
            std::cout << "Objects pass each other harmlessly\n";
            return;
        }
    }
    it->second();
}
#endif
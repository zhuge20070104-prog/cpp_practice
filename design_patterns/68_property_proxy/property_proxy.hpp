#ifndef _FREDRIC_PROPERTY_PROXY_HPP_
#define _FREDRIC_PROPERTY_PROXY_HPP_
#include <string>
#include <iostream>
#include <functional>

#include "log.h"

template <typename T>
struct Property {
    T value;
    std::function<bool(T)> func;

    Property(T value_, std::function<bool(T)> const& func_=nullptr): func(func_) {
        *this = value_;
    }

    operator T() {
        return value;
    }

    T operator=(T new_value) {
        B_LOG(info) << "Assignment\n";
        if(!func || func(new_value)) {
            value = new_value;
        } else {
            B_LOG(info) << "Validation failed, return source value\n";
        }
        return value;
    }
};

struct StrengthValidation {
    bool operator()(int strength) {
        return strength > 10 && strength < 20;
    }
};

struct Creature {
    Property<int> strength{10, StrengthValidation()};
    Property<int> agility {5};
};
#endif
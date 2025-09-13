#ifndef _FREDRIC_FLY_WEIGHT_HPP_
#define _FREDRIC_FLY_WEIGHT_HPP_

#include <string>
#include <iostream>
#include <sstream>
#include <boost/bimap.hpp>

using Key = uint32_t;

struct User {
    User(std::string const& first_name_, std::string const& last_name_): first_name(add(first_name_)), last_name(add(last_name_)){}

    // 根据 Key找value
    std::string const& get_first_name() const {
        return names.left.find(first_name)->second;
    }

    std::string const& get_last_name() const {
        return names.left.find(last_name)->second;
    }

    friend std::ostream& operator<<(std::ostream& os, User const& user) {
        os << "First Name Id: " << user.first_name << " First Name: " << user.get_first_name() << "\t"
            << "Last Name Id: " << user.last_name << " Last Name: " << user.get_last_name();
        return os;
    }

protected:
    Key first_name, last_name;
    static boost::bimap<Key, std::string> names;
    static Key seed;
    static Key add(std::string const& s) {
        auto it = names.right.find(s);

        // 在names中没找着，直接插
        if(it == names.right.end()) {
            Key id = ++seed;
            names.insert({id, s});
            return id;
        }

        // 找到了，直接返回Key
        return it->second;
    }
};

Key User::seed {0};
boost::bimap<Key, std::string> User::names {};

#endif
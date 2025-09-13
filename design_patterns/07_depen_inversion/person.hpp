#ifndef _FREDRIC_PERSON_HPP_
#define _FREDRIC_PERSON_HPP_

#include <string>
#include <iostream>
#include <vector>
#include <tuple>
#include <memory>

enum class RelationShip {
    Parent,
    Child,
    Sibling
};

struct Person {
    std::string name;
};

struct RelationBrowser {
    virtual std::vector<Person> find_all_children_of(std::string const& name) = 0;
};

struct RelationShips: public RelationBrowser {
    std::vector<std::tuple<Person, RelationShip, Person>> relations;

    void add_parent_and_child(Person const& parent, Person const& child) {
        relations.emplace_back(parent, RelationShip::Parent, child);
        relations.emplace_back(child, RelationShip::Child, parent);
    }

    std::vector<Person> find_all_children_of(std::string const& name) override {
        std::vector<Person> result;
        for(auto const& ele: relations) {
            auto first = std::get<0>(ele);
            auto relation = std::get<1>(ele);
            auto second = std::get<2>(ele);
            if(first.name == name && relation == RelationShip::Parent) {
                result.push_back(second);
            }
        }
        return result;
    }
};

struct RSearch {
    std::unique_ptr<RelationBrowser> browser;

    RSearch(std::unique_ptr<RelationBrowser> browser_): browser(std::move(browser_)) {
    }

    void search_child(std::string const& name) {
        for(auto const& person: browser->find_all_children_of(name)) {
            std::cout <<  name << " has a child called: " << person.name << std::endl;
        }
    }
};
#endif
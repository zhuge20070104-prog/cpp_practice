#ifndef _FREDRIC_OBSERVER_WITH_DEPS_H_
#define _FREDRIC_OBSERVER_WITH_DEPS_H_
#include <vector>
#include <string>
#include <iostream>
#include <boost/signals2.hpp>

namespace sig = boost::signals2;

template <typename T>
struct Observerable {
    virtual ~Observerable() = default;

    // 观察者就是这个signal，一旦发生变化，就触发观察者的事件
    sig::signal<void(T&, std::string const&)> property_changed;
};

struct Person;
// 观察者
struct Observer {
    void operator()(Person& p, std::string const& prop_name) const;
};

class Person: public Observerable<Person> {
    int age;
public:
    explicit Person(int age_);
    int get_age() const;
    void set_age(int age_);
    bool get_can_vote() const;
};
#endif
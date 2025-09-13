#ifndef _FREDRIC_SINGLETON_HPP_
#define _FREDRIC_SINGLETON_HPP_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <memory>

class IFoo {
public:
    virtual ~IFoo() {}
    virtual std::string name() = 0;
};

struct Foo: public IFoo {
    static int id;
    Foo() {
        ++id;
    }

    std::string name() override {
        return "foo " + std::to_string(id);
    }
};

int Foo::id = 0;

struct Bar {
    std::shared_ptr<IFoo> foo;
};


#endif
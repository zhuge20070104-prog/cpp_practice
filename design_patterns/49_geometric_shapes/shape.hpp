#ifndef _FREDRIC_SHAPE_HPP_
#define _FREDRIC_SHAPE_HPP_

#include "log.h"
#include <memory>
#include <string>
#include <vector>

struct IGraphic {
    virtual void draw() = 0;
};

struct Circle: IGraphic {
    void draw() override {
        B_LOG(info) << "Circle" << std::endl;
    }
};

struct Group: IGraphic {
    std::string name;
    std::vector<std::shared_ptr<IGraphic>> graphics;

    Group(std::string const& name_): name(name_)  {}

    void draw() override {
        B_LOG(info) << "Group " << name << " contains: " << std::endl;

        for(auto const& graphic: graphics) {
            graphic->draw();
        }
    }
};
#endif
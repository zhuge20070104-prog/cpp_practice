#ifndef _FREDRIC_BUILDER_HPP_
#define _FREDRIC_BUILDER_HPP_

#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <memory>

struct HTMLElement {
    std::string name;
    std::string text;

    std::size_t const indent_size = 2;
    std::vector<HTMLElement> elements;

    HTMLElement() {}

    HTMLElement(std::string const& name_, std::string const& text_): name(name_), text(text_) {}

    std::string str(int indent=0) const {
        std::ostringstream oss;
        std::string i(indent_size* indent, ' ');
        oss << i << "<" << name << ">" << std::endl;
        if(text.size() > 0) {
            oss << std::string(indent_size*(indent + 1), ' ') << text << std::endl;
        }

        for(auto const& ele: elements) {
            oss << ele.str(indent + 1);
        }
        oss << i << "</" << name << ">" << std::endl;
        return oss.str();
    }
};


struct HTMLBuilder {
private:
    HTMLElement root;

    HTMLBuilder(std::string const& root_name) {
        root.name = root_name;
    }

public:
    static HTMLBuilder create(std::string const& root_name) {
        return HTMLBuilder{root_name};
    }

    HTMLBuilder& add_child(std::string const& child_name, std::string const& child_text) {
        HTMLElement e {child_name, child_text};
        root.elements.emplace_back(e);
        return *this;
    }

    operator HTMLElement() const {
        return root;
    }
};

#endif
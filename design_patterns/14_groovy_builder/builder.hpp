#ifndef _FREDRIC_BUILDER_HPP_
#define _FREDRIC_BUILDER_HPP_

#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <memory>


namespace html {
    struct Tag {
        std::string name;
        std::string text;

        std::vector<Tag> children;
        std::vector<std::pair<std::string, std::string>> attributes;

        friend std::ostream& operator<<(std::ostream& os, Tag const& tag) {
            os << "<" << tag.name;
            for(auto const& att: tag.attributes) {
                os << " " << att.first << "=\"" << att.second << "\"";
            }

            // 没有子tag，没有文本，直接结束
            if(tag.children.size() == 0 && tag.text.size() == 0) {
                os << "/>" << std::endl;
            } else {
                os << ">" << std::endl;
                if(tag.text.size()) {
                    os << tag.text << std::endl;
                }

                for(auto const& child: tag.children) {
                    os << child;
                }

                os << "</" << tag.name << ">" << std::endl;
            }
            return os;
        }

    protected:
        Tag(std::string const& name_, std::string const& text_): name(name_), text(text_) {}
        Tag(std::string const& name_, std::vector<Tag> const& childs_): name(name_), children(childs_) {}
    };

    struct P: public Tag {
        explicit P(std::string const& text_): Tag("p", text_) {}
        explicit P(std::initializer_list<Tag> const& children_): Tag("p", children_) {}
    };

    struct IMG: public Tag {
        explicit IMG(std::string const& url): Tag("img", "") {
            attributes.emplace_back("src", url);
        }
    };
}

#endif
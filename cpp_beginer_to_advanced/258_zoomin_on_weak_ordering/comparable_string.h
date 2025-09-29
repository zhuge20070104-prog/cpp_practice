#ifndef _FREDRIC_COMPARABLE_STRING_H_
#define _FREDRIC_COMPARABLE_STRING_H_

#include <iostream>
#include <string>
#include <utility>

class ComparableString {
public:
    ComparableString(std::string str): m_str{std::move(str)} {}
    std::weak_ordering operator<=>(const ComparableString& other) const {
        if(m_str.size() == other.m_str.size()) {
            return std::weak_ordering::equivalent;
        } else if(m_str.size() < other.m_str.size()) {
            return std::weak_ordering::less;
        } else {
            return std::weak_ordering::greater;
        }
    }

    bool operator==(const ComparableString& other) const {
        return (m_str.size() == other.m_str.size());
    }
private:
    std::string m_str{};
};

#endif
#ifndef _FREDRIC_CASE_INSENSITIVE_STRING_H_
#define _FREDRIC_CASE_INSENSITIVE_STRING_H_

#include <iostream>
#include <string>
#include <utility>


std::weak_ordering case_insensitive_compare(const char* str1, const char* str2) {
    std::string s1(str1);
    std::string s2(str2);

    for(auto& c: s1) {
        c = std::toupper(c);
    }

    for(auto& c: s2) {
        c = std::toupper(c);
    }

    if(s1.compare(s2) > 0) {
        return std::weak_ordering::greater;
    } else if(s1.compare(s2) < 0) {
        return std::weak_ordering::less;
    } else {
        return std::weak_ordering::equivalent;
    }
}

class CaseInsensitiveString {

public:
    CaseInsensitiveString(const std::string& str): m_str{str} {}

    CaseInsensitiveString(const char* str): m_str{str} {}

    std::weak_ordering operator<=>(const CaseInsensitiveString& other) const {
        return case_insensitive_compare(m_str.c_str(), other.m_str.c_str());
    }

    std::weak_ordering operator<=>(const char* other) const {
        return case_insensitive_compare(m_str.c_str(), other);
    }

    bool operator==(const CaseInsensitiveString& other) const {
        return case_insensitive_compare(m_str.c_str(), other.m_str.c_str()) == std::weak_ordering::equivalent;
    }
private:
    std::string m_str;
};

#endif
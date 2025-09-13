#include "strc.h"
#include <cstdio>
#include <cstring>
#include <memory>

std::size_t strc::_maxlen = 1024;
char strc::_strc_class[] = "strc";

void strc::msg(char const* s) {
    if(data) printf("%s: %s (%s)\n", _strc_class, s, data);
    else printf("%s: %s\n", _strc_class, s);
    fflush(stdout); 
}

strc::strc(): data(nullptr) {
    msg("default ctor");
}


strc::strc(char const* s) {
    std::size_t slen = strnlen(s, _maxlen);
    data = new char[slen + 1];
    data[slen] = 0;
    memcpy(data, s, slen);
    msg("cstring ctor");
}


strc::strc(strc const& rhs) {
    std::size_t slen = strnlen(rhs.data, _maxlen);
    data = new char[slen + 1];
    data[slen] = 0;
    memcpy(data, rhs.data, slen);
    msg("copy ctor");
}


strc::strc(strc&& rhs) {
    data = std::move(rhs.data);
    rhs.data = nullptr;
    msg("move ctor");
}

strc::~strc() {
    msg("dtor");
    delete []data;
}

strc& strc::operator=(strc o) {
    swap(o);
    msg("copy and swap =");
    return *this;
}

char const* strc::value() const {
    return data;
}

strc::operator char const*() const {
    return value();
}

void strc::swap(strc& rhs) {
    std::swap(data, rhs.data);
}

bool strc::operator==(strc const& rhs) const {
    return strcmp(data, rhs.data) == 0;
}



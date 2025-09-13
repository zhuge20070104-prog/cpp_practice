#ifndef _FREDRIC_STRC_H_
#define _FREDRIC_STRC_H_
#include <cstdio>
#include <cstring>


class strc {
public:
    void msg(char const* s);
    strc();
    strc(char const* s);
    strc(strc const& rhs);
    strc(strc&& rhs);
    ~strc();
    strc& operator=(strc o);
    char const* value() const;
    operator char const*() const;
    void swap(strc& rhs);
    bool operator==(strc const& rhs) const;

private:
    char* data;
    static std::size_t _maxlen;
    static char _strc_class[];
};
#endif
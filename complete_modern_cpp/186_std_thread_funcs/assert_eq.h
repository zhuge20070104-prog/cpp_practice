#ifndef _FREDRIC_ASSERT_EQ_H_
#define _FREDRIC_ASSERT_EQ_H_

#include <initializer_list>

template <typename IT, typename Ele>
void ASSERT_LIST_EQ(IT begin, IT end, std::initializer_list<Ele> const& expects) {
    for(auto actual = begin, exp=std::begin(expects); actual!=end && exp!=std::end(expects); ++actual, ++exp) {
        ASSERT_EQ(*actual, *exp);
    }
}

#endif
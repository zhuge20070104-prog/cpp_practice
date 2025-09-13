#ifndef _FREDIRC_HASH_H_
#define _FREDRIC_HASH_H_

#include <cstddef>
#include <boost/container_hash/hash.hpp>

template <typename IT>
inline size_t hash_range(IT first, IT last) {
    size_t hash = 0;
    for(; first!=last; ++first) {
        boost::hash_combine(hash, *first);
    }
    return hash;
}

// Hash 一个支持迭代器的顺序容器
template <typename SEQ> 
struct hash_seq {
    size_t operator()(SEQ const& x) const {
        return hash_range(x.begin(), x.end());
    }
};
#endif
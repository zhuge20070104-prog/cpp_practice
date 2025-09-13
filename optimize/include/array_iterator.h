#ifndef _FREDRIC_ARRAY_ITERATOR_H_
#define _FREDRIC_ARRAY_ITERATOR_H_
#include <cstddef>

// 获取c style array 大小的模板方法
namespace std {
    template <typename T, int N>
    size_t size(T (&a) [N]) {
        return N;
    }
};

#endif
#ifndef _FREDRIC_FIXED_STRING_H_
#define _FREDRIC_FIXED_STRING_H_

#include <array>

/**
 * basic_fixed_string 是一个创建char[]类型对象的实验，char[]类型数组可以通过一个字面量进行创建
 * 这个类没有进行过性能测试
 * 
 * basic_fixed_string 是一个std::array<T>类型的变量，加一些构造函数
*/

template <unsigned N=10, typename T = char>
class basic_fixed_string: public std::array<T, N> {
public:
    basic_fixed_string() {
        for(auto it=this->begin(); it!=this->end(); ++it) {
            *it = 0;
        }
    }

    basic_fixed_string(T const* p) {
        for(auto it=this->begin(); it!=this->end(); ++it) {
            if(*p) {
                *it = *p;
                ++p;
            } else {
                *it=0;
            }
        }
    }

    basic_fixed_string& operator=(basic_fixed_string const& rhs){
        std::copy(rhs.begin(), rhs.end(), this->begin());
        return *this;
    }

    basic_fixed_string& operator=(T const* rhs) {
        for(auto it=this->begin(); it!=this->end(); ++it) {
            if(*rhs) {
                *it = *rhs;
                ++ rhs;
            } else {
                *it = 0;
            }
        }
    }
};
#endif
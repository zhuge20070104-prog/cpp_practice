#ifndef _FREDRIC_PRINT_HPP_
#define _FREDRIC_PRINT_HPP_

#include <initializer_list>

// 使用std::initializer_list传递参数，所有参数都必须是同一类型，不是同一类型就无法通过编译
template <typename T>
void print_list(std::initializer_list<T> const& args) {
    for(auto const& arg: args) {
        std::cout << arg << " ";
    }
    std::cout << std::endl;
}

// 需要一个空的print函数来终止递归
void print() {

}

// 我们不能直接使用可变模板参数，必须使用递归的方式来使用，
// 递归的方式需要一个递归终止条件，这里叫基础情况函数
// 这个基础情况函数不包含可变模板参数
template <typename T, typename ... Args>
void print(T a, Args ... args){
    std::cout << a << " ";
    print(args...);
}



#endif
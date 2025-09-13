#ifndef _FREDRIC_PRINT_HPP_
#define _FREDRIC_PRINT_HPP_


// 需要一个空的print函数来终止递归
void print() {
    // 最后一个输出后，打印换行符
    std::cout << std::endl;
}

// 我们不能直接使用可变模板参数，必须使用递归的方式来使用，
// 递归的方式需要一个递归终止条件，这里叫基础情况函数
// 这个基础情况函数不包含可变模板参数

// 使用常量引用,避免拷贝
template <typename T, typename ... Args>
void print(T const& a, Args const&  ... args){
    std::cout << a;
    // 最后一个参数不打印 ,
    if(sizeof...(args) != 0) {
        std::cout << ", ";
    }
    print(args...);
}



#endif
#ifndef _FREDRIC_STACK_HPP_
#define _FREDRIC_STACK_HPP_
#include <cstddef>

// 类模板也可以使用非类型参数，例如 int size, 他是一个编译期常量，可以用作数组大小
template <typename T, int size>
class Stack {
    T m_buffer[size];
    int m_top{-1};
public:
    // 创建默认构造函数
    Stack() = default;
    // 创建拷贝构造函数
    // 拷贝构造函数逐个拷贝
    Stack(Stack const& obj) {
        m_top = obj.m_top;
        for(int i=0; i<=m_top; ++i) {
            m_buffer[i] = obj.m_buffer[i];
        }
    }
    void push(T const& ele) {
        m_buffer[++m_top] = ele;
    }

    void pop();

    T const& top() const {
        return m_buffer[m_top];
    }

    bool empty() {
        return m_top == -1;
    }

    static Stack create();
};

// 模板函数只有在调用时才会实例化， 没有被调用的模板函数，不会被实例化
// 模板函数可以在类内实现，也可以在类外实现
// 在类外实现时，模板参数是类的一部分，如下
template <typename T, int size>
void Stack<T, size>::pop() {
    --m_top;
}

// 类内部可以简写，类外部必须全名
template <typename T, int size>
Stack<T, size> Stack<T, size>::create() {
    return Stack<T, size>(); 
}

#define MAKE_STACK(T, size) Stack<T, size>::create()


#endif
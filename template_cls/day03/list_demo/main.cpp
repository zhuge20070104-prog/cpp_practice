#include <iostream>
#include <stdexcept>

template <class T>
class list {
public:

    list(): m_head(nullptr), m_tail(nullptr) {}

    bool empty() {
        return m_head == nullptr && m_tail == nullptr;
    }

    void push_front(T const& data) {
        m_head = new node(nullptr, data, m_head);
        if(m_head->m_next) { // 不是空链表
        // 双向链表
            m_head->m_next->m_prev = m_head;
        } else {
            m_tail = m_head;
        }
    }

    void pop_front() {
        if(empty()) {
            return;
        }

        node* pnode = m_head->m_next;
        delete m_head;
        if(pnode) { // 剩下的不是空链表，清空前节点指针
            pnode->m_prev = nullptr;
        }else {
            // 仅存的节点被删除了
            m_tail = nullptr;
        }

        m_head = pnode;
    }

    // 获取头结点元素
    T& front() {
        if(empty()) {
            throw std::underflow_error("null node");
        }

        return m_head->m_data;
    }

    T const& front() const {
        return const_cast<list*>(this)->front();
    }

    // 添加尾节点
    void push_back(T const& data) {
        m_tail = new node(m_tail, data, nullptr);
        if(m_tail->m_prev) {
            m_tail->m_prev->m_next = m_tail;
        } else {
            m_head = m_tail;
        }
    }

    // 删除尾节点
    void pop_back() {
        if(empty()) {
            return;
        }

        node* pnode = m_tail->m_prev;
        delete m_tail;
        if(pnode) {
            pnode->m_next = nullptr;
        } else {
            m_head = nullptr;
        }

        m_tail = pnode;
    }

    // 获取尾节点数据
    T& back() {
        if(empty()) {
            throw std::underflow_error("null node");
        }
        return m_tail->m_data;
    }

    T const& back() const {
        return const_cast<list*>(this)->back();
    }

    // 清空链表
    void clear() {
        while(!empty()) {
            pop_front();
        }
    }





    std::size_t size() {
        std::size_t i = 0;
        for(node* pnode = m_head; pnode; pnode=pnode->m_next) {
            ++i;
        }
        return i;
    }
private:
    class node{
    public:
        node(node* prev, T const& data, node* next):
            m_prev(prev), m_data(data), m_next(next) {}
        node* m_prev;
        T m_data;
        node* m_next;
    };

    node* m_head;
    node* m_tail;

public:
    // 正向非常迭代类
    class iterator {
    public:
        iterator(node* start, node* cur, node* end): m_start(start), m_cur(cur), m_end(end) {}

        T& operator*() {
            if(m_cur == nullptr) {
                throw std::underflow_error("null node");
            }

            return m_cur->m_data;
        }

        iterator& operator++() {
            if(m_cur == nullptr) {
                m_cur = m_start;
            } else {
                m_cur = m_cur->m_next;
            }
            return *this;
        }

        iterator& operator--() {
            if(m_cur == nullptr) {
                m_cur = m_end;
            }else {
                m_cur = m_cur->m_prev;
            }
            return *this;
        }

        bool operator==(iterator const& that) const {
            return m_start == that.m_start && m_cur == that.m_cur && m_end == that.m_end;
        }

        bool operator!=(iterator const& that) const {
            return !(*this == that);
        }
    private:
        node* m_start;  // 开始指向
        node* m_cur;   // 当前指向
        node* m_end;   // 终止指向
        friend class list;
    };

    // 起始迭代器
    iterator begin() {
        return iterator(m_head, m_head, m_tail);
    }

    // 终止迭代器
    iterator end() {
        return iterator(m_head, nullptr, m_tail);
    }

    // 迭代器指向的位置添加节点
    void insert(iterator const& loc, T const& data) {
        // 在最后
        if(loc == end()) {
            push_back(data);
        } else {
            node* pnode = new node(loc.m_cur->m_prev, data, loc.m_cur);
            if(pnode->m_prev) {
                pnode->m_prev->m_next = pnode;
            }else {
                m_head = pnode;
            }

            pnode->m_next->m_prev = pnode;
        }
    }

    // 删除迭代器 指向的节点
    void erase(iterator const& loc) {
        if(loc == end()) {
            return;
        }

        node* pdel = loc.m_cur;
        if(pdel->m_prev) {
            pdel->m_prev->m_next = pdel->m_next;
        } else {
            m_head = pdel->m_next;
        }

        if(pdel->m_next) {
            pdel->m_next->m_prev = pdel->m_prev;
        } else {
            m_tail = pdel->m_prev;
        }

        delete pdel;
    }

    // 正向常迭代类
    class const_iterator {
    public:
        const_iterator(iterator const& it):m_it(it) {}
        T const& operator*() {
            return *m_it;
        }

        const_iterator& operator++() {
            ++m_it;
            return *this;
        }

        const_iterator& operator--() {
            --m_it;
            return *this;
        }

        bool operator==(const_iterator const& that) const {
            return m_it == that.m_it;
        }

        bool operator!=(const_iterator const& that) const {
            return !(*this == that);
        }
    private:
        iterator m_it;
    };

    const_iterator begin() const {
        return iterator(m_head, m_head ,m_tail);
    }

    const_iterator end() const {
        return iterator(m_head, nullptr, m_tail);
    }
};

// 比较查找, 利用 == 符号
template <class IT, class T>
IT find(IT const& a, IT const& b, T const& data) {
    for(IT it = a; it!=b; ++it) {
        if(*it == data) {
            return it;
        }
    }
    return b;
}


// 快速排序 < 
template <class IT>
void sort(IT const& begin, IT const& end) {
    IT p = begin;
    IT last = end;
    // 最后一个迭代器可能是空
    -- last;
    for(IT i=begin, j=last; i!=j;) {
        while(i!=p && *i<*p) {
            ++i;
        }

        if(i!=p) {
            std::swap(*i, *p);
            p = i;
        }

        while(j!=p && *p<*j) {
            --j;
        }
        if(j!=p) {
            std::swap(*p, *j);
            p = j;
        }
    }

    IT it = begin;
    ++it;

    if(p!=begin && p!= it) {
        sort(begin, p);
    }

    it = p;
    ++it;
    if(it!=end && it!=last) {
        sort(it, end);
    }
}

// 快速排序，比较器方法
template <class IT, class CMP>
void sort(IT const& begin, IT const& end, CMP cmp) {
    IT p = begin;
    IT last = end;
    // 最后一个迭代器可能是空
    -- last;
    for(IT i=begin, j=last; i!=j;) {
        while(i!=p && cmp(*i, *p)) {
            ++i;
        }

        if(i!=p) {
            std::swap(*i, *p);
            p = i;
        }

        while(j!=p && cmp(*p, *j)) {
            --j;
        }
        if(j!=p) {
            std::swap(*p, *j);
            p = j;
        }
    }

    IT it = begin;
    ++it;

    if(p!=begin && p!= it) {
        sort(begin, p, cmp);
    }

    it = p;
    ++it;
    if(it!=end && it!=last) {
        sort(it, end, cmp);
    }
}


// 以上代码模拟标准库容器

// 以下代码模拟普通用户

template <class T>
void print(std::string const& str, list<T> const& ls) {
    std::cout << str <<std::endl;
    for(auto ele: ls) {
        std::cout << ele << ' ';
    }
    std::cout << std::endl << "-------------------------" << std::endl;
}


int main(int argc, char* argv[]) {
    list<int> ls;

    for(int i=0; i<5; ++i) {
        ls.push_front(10 + i);
    }

    for(int i=0; i<5; ++i) {
        ls.push_back(100 + i);
    }

    print("添加节点后: ", ls);
    ls.pop_front();
    ls.pop_back();

    print("删除头尾节点后: ", ls);

    ls.insert(++ls.begin(), 1000);
    print("在迭代器指向的位置添加节点以后: ", ls);

    ls.erase(ls.begin());
    print("删除迭代器指向的节点以后: ", ls);

    auto it = ls.begin();
    *it = 800;
    print("更改迭代器指向的节点以后: ", ls);

    auto fit = find(ls.begin(), ls.end(), 100);
    if(fit != ls.end()) {
        ls.erase(fit);
    }

    print("找到100并删除后: ", ls);


    sort(ls.begin(), ls.end(), [](int const& a, int const& b){
        return a>b;
    });

    print("排序后: ", ls);

    
    return EXIT_SUCCESS;
}

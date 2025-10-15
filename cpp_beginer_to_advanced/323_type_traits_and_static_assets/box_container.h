#ifndef _FREDRIC_BOX_CONTAINER_H
#define _FREDRIC_BOX_CONTAINER_H

#include <iostream>
#include <type_traits>

template <typename T>
class BoxContainer {
    static_assert(std::is_default_constructible_v<T>, "Type in the BoxContainer should have a default ctor");
    static const std::size_t DEFAULT_CAPACITY {30};
    static const std::size_t EXPAND_STEPS {5};
public:
    friend std::ostream& operator<< <T>(std::ostream& os, const BoxContainer<T>& box);
    BoxContainer(std::size_t capacity=DEFAULT_CAPACITY);
    BoxContainer(const BoxContainer<T>& src);
    virtual ~BoxContainer();

    
    std::size_t size() const {return m_size;}
    std::size_t capacity() const {return m_capacity;}

    void add(const T& item);
    bool remove_item(const T& item);
    std::size_t remove_all(const T& item);

    T get_item(std::size_t index) const {return m_item[index];}

    void operator+=(const BoxContainer<T>& other);
    void operator=(const BoxContainer<T>& src);

private:
    void expand(std::size_t new_capacity);
private:
    T* m_item{};
    std::size_t m_size{};
    std::size_t m_capacity{};
};

template <typename T>
BoxContainer<T>::BoxContainer(std::size_t capacity):
    m_item{new T[capacity]},
    m_size{0},
    m_capacity{capacity} {}


template <typename T>
BoxContainer<T>::BoxContainer(const BoxContainer<T>& src):
    m_item{new T[src.m_capacity]},
    m_size{src.m_size},
    m_capacity{src.m_capacity} {
    
    for(std::size_t i=0; i<src.m_size; ++i) {
        m_item[i] = src.m_item[i];
    }
}

template <typename T>
BoxContainer<T>::~BoxContainer() {
    delete[] m_item;
}

template <typename T>
void BoxContainer<T>::expand(std::size_t new_capacity) {
    T* new_item {};
    if(new_capacity == m_capacity) {
        return;
    }

    new_item = new T[new_capacity];
    for(std::size_t i=0; i<m_size; ++i) {
        new_item[i] = m_item[i];
    }
    delete[] m_item;
    m_item = new_item;
    m_capacity = new_capacity;
}


template <typename T>
void BoxContainer<T>::add(const T& item) {
    if(m_size == m_capacity) {
        expand(m_capacity + EXPAND_STEPS);
    }

    m_item[m_size] = item;
    ++m_size;
}

template <typename T>
bool BoxContainer<T>::remove_item(const T& item) {
    std::size_t index {m_capacity + 999};
    
    for(std::size_t i=0; i<m_size; ++i) {
        if(m_item[i] == item) {
            index = i;
            break;
        }
    }

    if(index > m_size) {
        return false;
    }

  
    m_item[index] = m_item[m_size-1];
    --m_size;
    return true;
}

template <typename T>
std::size_t BoxContainer<T>::remove_all(const T& item) {
   std::size_t remove_count {0};
   bool removed {remove_item(item)};

   if(removed) {
    ++remove_count;
   }

   while(removed) {
    removed = remove_item(item);
    if(removed) {
        ++remove_count;
    }
   }
   return remove_count;
}

template <typename T>
void BoxContainer<T>::operator+=(const BoxContainer<T>& other) {
    if((m_size + other.m_size) > m_capacity) {
        expand(m_size + other.m_size);
    }

    for(std::size_t i=0; i<other.m_size; ++i) {
        m_item[m_size+i] = other.m_item[i];
    }

    m_size += other.m_size;
}

template <typename T>
void BoxContainer<T>::operator=(const BoxContainer<T>& src) {
    T* new_item {};

    if(this == &src) {
        return;
    }

    if(m_capacity != src.m_capacity) {
        new_item = new T[src.m_capacity];
        delete[] m_item;
        m_item = new_item;
        m_capacity = src.m_capacity;
    }

    for(std::size_t i=0; i<src.m_size; ++i) {
        m_item[i] = src.m_item[i];
    }
    m_size = src.m_size;    
}

template <typename T>
BoxContainer<T> operator+(const BoxContainer<T>& left, const BoxContainer<T>& right) {
    BoxContainer new_box(left.size() + right.size());
    new_box += left;
    new_box += right;
    return new_box;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const BoxContainer<T>& box) {
    for(std::size_t i=0; i<box.size(); ++i) {
        os << box.m_item[i] << " ";
    }
    return os;
}
#endif
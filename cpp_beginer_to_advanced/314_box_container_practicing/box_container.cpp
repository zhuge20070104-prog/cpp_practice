#include "box_container.h"

BoxContainer::BoxContainer(std::size_t capacity):
    m_item{new value_type[capacity]},
    m_size{0},
    m_capacity{capacity} {}


BoxContainer::BoxContainer(BoxContainer const& src):
    m_item{new value_type[src.m_capacity]},
    m_size{src.m_size},
    m_capacity{src.m_capacity} {
    
    for(std::size_t i=0; i<src.m_size; ++i) {
        m_item[i] = src.m_item[i];
    }
}

BoxContainer::~BoxContainer() {
    delete[] m_item;
}

void BoxContainer::stream_insert(std::ostream& os) const {
    os << "BoxContainer(size=" << m_size << ", capacity=" << m_capacity << ")";
    os << " Items: [";
    for(std::size_t i=0; i<m_size; ++i) {
        os << m_item[i] << " ";
    }
    os << "]";
}

void BoxContainer::expand(std::size_t new_capacity) {
    value_type* new_item {};
    if(new_capacity == m_capacity) {
        return;
    }

    new_item = new value_type[new_capacity];
    for(std::size_t i=0; i<m_size; ++i) {
        new_item[i] = m_item[i];
    }
    delete[] m_item;
    m_item = new_item;
    m_capacity = new_capacity;
}


void BoxContainer::add(const value_type& item) {
    if(m_size == m_capacity) {
        expand(m_capacity + EXPAND_STEPS);
    }

    m_item[m_size] = item;
    ++m_size;
}

bool BoxContainer::remove_item(const value_type& item) {
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

std::size_t BoxContainer::remove_all(const value_type& item) {
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

void BoxContainer::operator+=(const BoxContainer& other) {
    if((m_size + other.m_size) > m_capacity) {
        expand(m_size + other.m_size);
    }

    for(std::size_t i=0; i<other.m_size; ++i) {
        m_item[m_size+i] = other.m_item[i];
    }

    m_size += other.m_size;
}

void BoxContainer::operator=(const BoxContainer& src) {
    value_type* new_item {};

    if(this == &src) {
        return;
    }

    if(m_capacity != src.m_capacity) {
        new_item = new value_type[src.m_capacity];
        delete[] m_item;
        m_item = new_item;
        m_capacity = src.m_capacity;
    }

    for(std::size_t i=0; i<src.m_size; ++i) {
        m_item[i] = src.m_item[i];
    }
    m_size = src.m_size;    
}

BoxContainer operator+(const BoxContainer& left, const BoxContainer& right) {
    BoxContainer new_box(left.size() + right.size());
    new_box += left;
    new_box += right;
    return new_box;
}
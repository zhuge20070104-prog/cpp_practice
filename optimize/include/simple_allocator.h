#ifndef _FREDRIC_SIMPLE_ALLOCATOR_H_
#define _FREDRIC_SIMPLE_ALLOCATOR_H_

#include <limits>
#include <memory>

template <typename T>
class Allocator {
public:
    typedef T value_type;
    typedef T* pointer;
    typedef T const* const_pointer;
    typedef T& reference;
    typedef T const& const_reference;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;
public:
    template <typename U>
    struct rebind {
        typedef Allocator<U> other;
    };
public:
    Allocator() {}
    ~Allocator() {}
    Allocator(Allocator const&) {}
    template <typename U>
    explicit Allocator(Allocator<U> const&) {}

    const_pointer address(const_reference r) {
        return &r;
    }

    void construct(pointer p, T const& t) {
        new (p) T(t);
    }

    void destroy(pointer p) {
        p->~T();
    }

    size_type max_size() const {
        return std::numeric_limits<size_type>::max()/sizeof(T);
    }

    bool operator==(Allocator const&)  {
        return true;
    }

    bool operator!=(Allocator const& a) {
        return !operator==(a);
    } 

    pointer allocate(
        size_type count, 
        typename std::allocator<void>::const_pointer = 0
    ) {
        return reinterpret_cast<pointer>(::operator new(count* sizeof(T)));
    }

    void deallocate(pointer p, size_type) {
        ::operator delete(p);
    }

};
#endif
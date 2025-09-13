#ifndef _FREDRIC_OLD_BLOCK_ALLOCATOR_H_
#define _FREDRIC_OLD_BLOCK_ALLOCATOR_H_
#include <limits>
#include <memory>

// 快速的不好的fixed block分配器
// 实现上在查找free block时，有一个O(n)的复杂度，不好

class block_o_memory {
public:
    static unsigned const size = 8;
    static size_t const blocksize = 512;
    static void* allocate(std::size_t size);
    static void deallocate(void* p);
    static unsigned count();

private:
    static char mem_[size][blocksize];
    static bool free_[size]; // free_指示每个块是否空闲
};

template <typename T, size_t n>
class block_allocator {

public:

    typedef T value_type;
    typedef T* pointer;
    typedef T const* const_pointer;
    typedef T& reference;
    typedef T const& const_reference;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;

    pointer address(reference r) {
        return &r;
    }

    const_pointer address(const_reference r) {
        return &r;
    }
    
    template <typename U>
    struct rebind {
        typedef block_allocator<U, n> other;
    };

public:
    block_allocator() {}
    ~block_allocator() {}
    block_allocator(block_allocator const&) {}

    template <typename U>
    explicit block_allocator(block_allocator<U, n> const&) {}

    void construct(pointer p, T const& t) {
        return new (p) T(t);
    }

    void destroy(pointer p) {
        p->~T();
    }

    size_type max_size() const {
        return block_o_memory::blocksize;
    }

    bool operator==(block_allocator const& other) const {
        return true;
    }

    bool operator!=(block_allocator const& a) const {
        return !operator==(a);
    }

    pointer allocate(size_type count,
        typename std::allocator<void>::const_pointer = 0
    ) {
        return reinterpret_cast<pointer>(block_o_memory::allocate(count * sizeof(T)));
    }

    void deallocate(pointer p, size_type) {
        block_o_memory::deallocate(p);
    }
};
#endif
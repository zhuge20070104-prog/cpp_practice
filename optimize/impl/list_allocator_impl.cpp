#include "stopwatch11.h"
#include "block_mgr.h"

#include <limits>
#include <memory> 
#include <iostream>
#include <list>
#include <map>

char list_arena[80008];
fixed_block_memory_manager<fixed_arena_controller> list_memory_manager(list_arena);

template <typename T>
class StatelessListAllocator {
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
        typedef StatelessListAllocator<U> other;
    };

public:
    StatelessListAllocator() {}
    ~StatelessListAllocator() {}
    StatelessListAllocator(StatelessListAllocator const&) {}
    
    template <typename U>
    explicit StatelessListAllocator(StatelessListAllocator<U> const&) {

    }

    const_pointer address(const_reference r) {
        return &r;
    }

    pointer address(reference r) {
        return &r;
    }

    void construct(pointer p, T const& t) {
        new (p) T(t);
    }

    void destroy(pointer p) {
        p->~T();
    }

    size_type max_size() const {
        return list_memory_manager.capacity();
    }

    bool operator==(StatelessListAllocator const&) const {
        return true;
    }

    bool operator!=(StatelessListAllocator const& a) const {
        return !operator==(a);
    }

    pointer allocate(
        size_type count, typename std::allocator<void>::const_pointer /*hint*/ = nullptr
    ) {
        return reinterpret_cast<pointer>(list_memory_manager.allocate(count * sizeof(T)));
    }

    void deallocate(pointer p, size_type) {
        list_memory_manager.deallocate(p);
    }
};

int test_list_allocator(int test_no, unsigned long multiplier) {
    bool rc = true;
    switch(test_no) {
        default: return -1;
        case 0: return 3;
        case 1: {
            std::list<int, StatelessListAllocator<int>> l;
            for(unsigned i=0; i<100; ++i) {
                l.push_back(i);
            }
        }
            break;
        
        case 2: {
            {
                StopWatch sw("list push_back, default allocator");
                for(unsigned j=10*multiplier; j>0; --j) {
                    std::list<int> l;
                    for(unsigned i=0; i<1000; ++i) {
                        l.push_back(i);
                    }
                }
            }

            {
                StopWatch sw("list push_back, block allocator");
                for(unsigned j=10*multiplier; j>0; --j) {
                    std::list<int, StatelessListAllocator<int>> l;
                    for(unsigned i=0; i<1000; ++i) {
                        l.push_back(i);
                    }
                }
            }
        }
            break;
        
        case 3: {
            {
                StopWatch sw("map insert, default allocator");
                for(unsigned j=10* multiplier; j>0; --j) {
                    std::map<int, int> m;
                    for(unsigned i=0; i<1000; ++i) {
                        m[i] = 0;
                    }
                }
            }

            list_memory_manager.clear();

            {
                StopWatch sw("map insert, block allocator");
                for(unsigned j=10*multiplier; j>0; --j) {
                    std::map<int, int, std::less<int>, StatelessListAllocator<std::pair<const int, int>>> m;
                    for(unsigned i=0; i<1000; ++i) {
                        m[i] = 0;
                    }
                }
            }
        }
            break;
    }

    return (rc)? 1: 0;
}
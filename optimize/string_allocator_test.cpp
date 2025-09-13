#include <limits>
#include <memory>
#include <string>
#include <iostream>
#include "block_mgr.h"
#include "stopwatch11.h"
#include "test_driver.h"


char string_arena[25000];
fixed_block_memory_manager<fixed_arena_controller> string_memory_manager(string_arena);

template <typename T>
class StatelessStringAllocator  {
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
        typedef StatelessStringAllocator<U> other;
    };

public:
    StatelessStringAllocator() {}
    ~StatelessStringAllocator() {}
    StatelessStringAllocator(StatelessStringAllocator const&) {}

    template <typename U>
    explicit StatelessStringAllocator(StatelessStringAllocator<U> const&) {}

    const_pointer address(const_reference r) {
        return &r;
    }

    pointer address(reference r) {
        return &r;
    }

    // inplacement new
    void construct(pointer p, T const& t) {
        new(p) T(t);
    }

    void destroy(pointer p) {
        p->~T();
    }

    size_type max_size() const {
        return 512;
    }

    bool operator==(StatelessStringAllocator const&) const {
        return true;
    }

    bool operator!=(StatelessStringAllocator const& a) const {
        return !operator==(a);
    }

    pointer allocate(size_type /*count*/,
            typename std::allocator<void>::const_pointer /*hint*/ = nullptr) {
        return reinterpret_cast<pointer>(string_memory_manager.allocate(512));
    }

    void deallocate(pointer p, size_type) {
        string_memory_manager.deallocate(p);
    }
};

typedef std::basic_string<
    char,
    std::char_traits<char>,
    StatelessStringAllocator<char>> fixed_block_string;

// original, naive remove_ctrl()
std::string remove_ctrl(std::string s) {
    std::string result;
    for(std::size_t i=0; i<s.length(); ++i) {
        if(s[i] >= 0x20) {
            result = result + s[i];
        }
    }
    return result;
}

// use fixed_block_string to substitude some of the instances.
fixed_block_string remove_ctrl_fixed_block(std::string s) {
    fixed_block_string result;
	for (size_t i = 0; i<s.length(); ++i) {
		if (s[i] >= 0x20)
			result = result + s[i];
	}
	return result;
}


int test_string_allocator(int test_no, unsigned long multiplier) {
    typedef unsigned counter_t;
    counter_t const iterations = 100* multiplier;
    std::string s("\07Now is the time\07 for all good men\r\n to come to the aid of their country. \07");
	std::string test("Now is the time for all good men to come to the aid of their country. ");
    s = s + s + s;
    test = test + test + test;

    std::string stdresult;
    fixed_block_string fbresult;

    bool rc = true;
    switch(test_no) {
        default: return -1;
        case 0: return 2;
        case 1:
            std::cout << s.length() << " character argument to remove_ctrl()" << std::endl;
            std::cout << iterations << " iterations" << std::endl;
            {
                std::string verifier;
                verifier = remove_ctrl(s);
                rc &= (verifier.compare(test) == 0);

                fixed_block_string result2 = remove_ctrl_fixed_block(s);
                verifier = result2.data();
                rc &= (verifier.compare(test) == 0); 
            }
        break;
        case 2:
            {
                StopWatch sw("remove_ctrl()");
                for(counter_t i=0; i<iterations; ++i) {
                    stdresult = remove_ctrl(s);
                }
            }
            {
                StopWatch sw("remove_ctrl_fixed_block()");
                for(counter_t i=0; i<iterations; ++i) {
                    fbresult = remove_ctrl_fixed_block(s);
                }
            }
        break;
    }

    return rc? 1: 0;
}

int main(int argc, char* argv[]) {
    test_driver(test_string_allocator, argc, argv);
    return EXIT_SUCCESS;
}

 


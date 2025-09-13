// from Optimized C++, (c) Copyright 2015, by Kurt Guntheroth, All Rights Reserved
// fixed array memory manager to use with class-specific new

#ifndef _FREDRIC_BLOCK_MGR_INC_
#define _FREDRIC_BLOCK_MGR_INC_
#include <memory>
#include <algorithm>

// fixed block memory manager
template <class	Arena>
template <int N>
inline fixed_block_memory_manager<Arena>::fixed_block_memory_manager(char (&a) [N]):
	arena_(a), free_ptr_(nullptr), block_size_(0) {
}


template <class Arena>
inline void* fixed_block_memory_manager<Arena>::allocate(std::size_t size) {
	if(empty()) {
		free_ptr_ = reinterpret_cast<free_block*>(arena_.allocate(size));
		block_size_ = size;
		if(empty()) {
			throw std::bad_alloc();
		}
	}

	if(size > block_size_) {
		throw std::bad_alloc();
	}

	auto p = free_ptr_;
	free_ptr_ = free_ptr_->next;
	return p;
}

template <class Arena>
inline std::size_t fixed_block_memory_manager<Arena>::block_size() const {
	return arena_.block_size();
}


template <class Arena>
inline std::size_t fixed_block_memory_manager<Arena>::capacity() const {
	return arena_.capacity();
}


template <class Arena>
inline void fixed_block_memory_manager<Arena>::deallocate(void* p) {
	if(p == nullptr) {
		return;
	}

	auto fp = reinterpret_cast<free_block*>(p);
	fp->next = free_ptr_;
	free_ptr_ = fp;
}


template <class Arena>
inline void fixed_block_memory_manager<Arena>::clear() {
	free_ptr_ = nullptr;
	arena_.clear();
}

template <class Arena>
inline bool fixed_block_memory_manager<Arena>::empty() const {
	return free_ptr_ == nullptr;
}




///fixed_arena_controller///////
template <int N>
inline fixed_arena_controller::fixed_arena_controller(char (&a) [N]):arena_(a),arena_size_(N), block_size_(0) {}

inline void* fixed_arena_controller::allocate(std::size_t size) {
	if(!empty()) {
		return nullptr; // arena already allocated
	}

	block_size_ = std::max(size, sizeof(void*));
	std::size_t count = capacity();
	if(count == 0) {
		return nullptr;  // arena not big enough for even one item
	}

	char* p;
	for(p=(char*)arena_; count>1; --count, p+=block_size_) {
		*reinterpret_cast<char**>(p) = p + block_size_;
	}
	*reinterpret_cast<char**>(p) = nullptr;
	return arena_;
}


inline std::size_t fixed_arena_controller::block_size() const {
	return block_size_;
}

inline std::size_t fixed_arena_controller::capacity() const {
	return block_size_? (arena_size_/block_size_): 0;
}

inline void fixed_arena_controller::clear() {
	block_size_ = 0;
}

inline bool fixed_arena_controller::empty() const {
	return block_size_ == 0;
}


#endif
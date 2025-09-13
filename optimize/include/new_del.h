#ifndef _FREDRIC_NEW_DEL_H_
#define _FREDRIC_NEW_DEL_H_

#include <cstddef>
extern bool new_instrumentation_on;

void instrument_new(bool f = true);

struct new_instrument {
public:
    new_instrument();
    ~new_instrument();
};


// std::hex 转16进制输出
// std::dec 转10进制输出
// std::oct 转8进制输出
void* operator new(std::size_t size) noexcept(false);
void* operator new[](std::size_t size) noexcept(false);
void operator delete(void *p) noexcept(true);
void operator delete[](void* p) noexcept(true);

#endif
#include <string>
#include <exception>
#include <stdexcept>

std::string insert_ctrl(std::string& s) {
    char buf[10000];
    char* dest = buf;
    char* end = buf + sizeof(buf) - 4;

    char const* src = s.data();
    std::size_t count = s.length();
    while(count > 0 && dest < end) {
        if(*src < 0x20 && dest < end) {
            *dest++ = '\\';
            *dest++ = 'x';
            *dest++ = "0123456789ABCDEF"[*src >> 4];
            *dest++ = "0123456789ABCDEF"[*src & 0xf];
            ++src;
        } else if(dest < buf + sizeof(buf)){
            *dest++ = *src++;
        } else {
            throw std::logic_error("string too long");
        }
        --count;
    }

    return std::move(std::string(buf, dest));
}

int test_insert_ctrl(int test_no, unsigned long multiplier) {
    bool rc = true;
    switch (test_no) {
    default:
        return -1;
    case 0:
        return 1;
    case 1: {
        std::string s = "test";
        rc &= (insert_ctrl(s) == std::string("test"));
        s = "test\07";
        rc &= (insert_ctrl(s) == std::string("test\\x07"));
        s = "x\01test\07";
        rc &= (insert_ctrl(s) == std::string("x\\x01test\\x07"));
    }   
        break; 
    }

    return (rc) ? 1: 0;
}
#ifndef _FREDRIC_KVSTRUCT_H_
#define _FREDRIC_KVSTRUCT_H_
#include <cstring>


// simple, non-template key/value class with char[] keys, unsigned values
struct kvstruct {
    char key[9];
    unsigned value; 

    kvstruct(unsigned k): value(k) {
        char buf[9];
        strcpy(key, stringify(k, buf));
    }

    // Dec to Hex 
    static char const* stringify(unsigned i, char* buf) {
        buf[8] = 0;
        char* bufp = &buf[8];
        do {
            *--bufp = "0123456789ABCDEF"[i & 0xf];
            i >>= 4;
        } while(i!=0);
        return bufp;
    }

    bool operator<(kvstruct const& that) const { return strcmp(this->key, that.key) < 0; }
    bool operator==(kvstruct const& that) const { return strcmp(this->key, that.key) == 0; }
};

#endif
#ifndef _FREDRIC_STREAM_INSERTABLE_H
#define _FREDRIC_STREAM_INSERTABLE_H

#include <iostream>

class StreamInsertable {
    friend std::ostream& operator<<(std::ostream& os, const StreamInsertable& stream_insertable);
public:
    virtual void stream_insert(std::ostream& os) const = 0;
};

#endif
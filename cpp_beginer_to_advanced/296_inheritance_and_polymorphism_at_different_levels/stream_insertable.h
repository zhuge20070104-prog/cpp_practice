#ifndef _FREDRIC_STREAM_INSERTABLE_H_
#define _FREDRIC_STREAM_INSERTABLE_H_

#include <iostream>

class StreamInsertable {
    friend std::ostream& operator<<(std::ostream& os, const StreamInsertable& operand);
public:
    virtual void stream_insert(std::ostream& os) const = 0;
};
#endif
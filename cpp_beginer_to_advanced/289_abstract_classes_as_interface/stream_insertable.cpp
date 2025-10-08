#include "stream_insertable.h"

std::ostream& operator<<(std::ostream& os, const StreamInsertable& stream_insertable) {
    stream_insertable.stream_insert(os);
    return os;
}
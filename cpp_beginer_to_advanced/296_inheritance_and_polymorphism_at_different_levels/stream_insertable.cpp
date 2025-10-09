#include "stream_insertable.h"

std::ostream& operator<<(std::ostream& os, const StreamInsertable& operand) {
    operand.stream_insert(os);
    return os;
}
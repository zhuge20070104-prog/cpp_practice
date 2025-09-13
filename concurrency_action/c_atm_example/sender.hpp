#ifndef _FREDRIC_MSG_SENDER_HPP_
#define _FREDRIC_MSG_SENDER_HPP_

#include "threadsafe_queue.hpp"

namespace messaging {
    class sender {
        queue* q;
    public:
        sender(): q(nullptr) {}

        explicit sender(queue* q_): q(q_) {}        

        template <typename Msg>
        void send(Msg const& msg) {
            if(q) {
                q->push(msg);
            }
        }
    };
};
#endif
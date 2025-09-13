#ifndef _FREDRIC_MSG_RECEIVER_HPP_
#define _FREDRIC_MSG_RECEIVER_HPP_

#include "threadsafe_queue.hpp"
#include "sender.hpp"
#include "dispatcher.hpp"

namespace messaging {
    class receiver {
        queue q;

    public: 
        operator sender() {
            return sender(&q);
        }   

        dispatcher wait() {
            return dispatcher(&q);
        }
    };
};
#endif
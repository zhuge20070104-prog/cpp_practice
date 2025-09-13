#ifndef _FREDRIC_MSG_DISPATCHER_HPP_
#define _FREDRIC_MSG_DISPATCHER_HPP_

#include "threadsafe_queue.hpp"

namespace messaging {
    class close_queue {};

    template <typename PreviousDispatcher, typename Msg, typename Func>
    class TemplateDispatcher {  
        queue* q;
        PreviousDispatcher* prev;
        Func f;
        bool chained;

        TemplateDispatcher(TemplateDispatcher const&) = delete;
        TemplateDispatcher& operator=(TemplateDispatcher const&) = delete;

        // 前向声明另一个TemplateDispatcher为友元，后面handle好用
        template <typename Dispatcher, typename OtherMsg, typename OtherFunc>
        friend class TemplateDispatcher;

        void wait_and_dispatch() {
            for(;;) {
                auto msg = q->wait_and_pop();
                if(dispatch(msg)) {
                    break;
                }
            }
        }

        bool dispatch(std::shared_ptr<message_base> const& msg) {
            if(wrapped_message<Msg>* wrapper = dynamic_cast<wrapped_message<Msg>*>(msg.get())) {
                f(wrapper->contents);
                return true;
            }else {
                return prev->dispatch(msg);
            }
        }

    public:
        TemplateDispatcher(TemplateDispatcher&& other):
            q(other.q), prev(other.prev), f(std::move(other.f)),
            chained(other.chained)  {
                other.chained = true;
        }

        TemplateDispatcher(queue* q_, PreviousDispatcher* prev_, Func&& f_):
            q(q_), prev(prev_), f(std::forward<Func>(f_)), chained(false) {
                prev_->chained = true;
        }

        template <typename OtherMsg, typename OtherFunc>
        TemplateDispatcher<TemplateDispatcher, OtherMsg, OtherFunc>
        handle(OtherFunc&& of) {
            return TemplateDispatcher<TemplateDispatcher, OtherMsg, OtherFunc>(
                q, this, std::forward<OtherFunc>(of)
            );
        }

        ~TemplateDispatcher() noexcept(false) {
            if(!chained) {
                wait_and_dispatch();
            }
        }
    };

    class dispatcher {
        queue* q;
        bool chained;

        dispatcher(dispatcher const&) = delete;
        dispatcher& operator=(dispatcher const&) = delete;

        // 声明TemplateDispatcher，后面好用
        template <
            typename Dispatcher,
            typename Msg,
            typename Func
        >        
        friend class TemplateDispatcher;

        void wait_and_dispatch() {
            for(;;) {
                auto msg = q->wait_and_pop();
                dispatch(msg);
            }
        }

        bool dispatch(std::shared_ptr<message_base> const& msg) {
            // 发现是close_queue类型的消息，throw close_queue,退出
            if(dynamic_cast<wrapped_message<close_queue>*>(msg.get())) {
                throw close_queue();
            }
            return false;
        }

    public:
        dispatcher(dispatcher&& other):
            q(other.q), chained(other.chained) {
            other.chained = true;
        }

        explicit dispatcher(queue* q_):
            q(q_), chained(false) {}
        
        template <typename Msg, typename Func>
        TemplateDispatcher<dispatcher, Msg, Func> 
        handle(Func&& f) {
            return TemplateDispatcher<dispatcher, Msg, Func>(q, this, std::forward<Func>(f));
        }

        ~dispatcher() noexcept(false) {
            if(!chained) {
                wait_and_dispatch();
            }
        }
    };
}
#endif
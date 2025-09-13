#ifndef _FREDRIC_NET_MESSAGE_H_
#define _FREDRIC_NET_MESSAGE_H_

#include "net_common.h"

namespace olc {
namespace net {

    template <typename T>
    struct message_header {
        T id{};
        uint32_t size = 0;
    };

    template <typename T>
    struct message {
        message_header<T> header{};
        std::vector<uint8_t> body;

        std::size_t size() const {
            return body.size();
        }

        // 输出操作符重载，std::cout 使用
        friend std::ostream& operator<<(std::ostream& os, message<T> const& msg) {
            os << "ID: " << int(msg.header.id) << " Size: " << msg.header.size;
            return os;
        }

        // 把POD类型的消息放入message
        template <typename DataType>
        friend message<T>& operator<<(message<T>& msg, DataType const& data) {
            static_assert(std::is_standard_layout<DataType>::value, "Data is too complex to be pushed into vector");

            std::size_t  i = msg.body.size();
            msg.body.resize(msg.body.size() + sizeof(DataType));
            std::memcpy(msg.body.data() + i, &data, sizeof(DataType));
            msg.header.size = msg.size();
            return msg;
        }

        // 将POD类型从buffer中读出来
        template <typename DataType>
        friend message<T>& operator>>(message<T>& msg, DataType& data) {
            static_assert(std::is_standard_layout<DataType>::value, "Data is too complex to be pulled from vector");

            std::size_t i = msg.body.size() - sizeof(DataType);
            std::memcpy(&data, msg.body.data() + i, sizeof(DataType));
            msg.body.resize(i);
            msg.header.size = msg.size();
            return msg;
        } 
    };

    // An "owned" message is identical to a regular message, but it is associated with
    // a connection. On a server, the owner would be the client that sent the message, 
    // on a client the owner would be the server.
    // Client 不需要owner, owner为空
    template <typename T>
    class connection;

    template <typename T> 
    class owned_message {
    public:
        std::shared_ptr<connection<T>> remote = nullptr;
        message<T> msg;

        // 一个友好的string maker
        friend std::ostream& operator<<(std::ostream& os, owned_message<T> const& msg) {
            os << msg.msg;
            return os;
        }
    };
}
}
#endif
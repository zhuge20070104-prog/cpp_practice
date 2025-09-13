#ifndef _FREDRIC_NET_CONNECTION_H_
#define _FREDRIC_NET_CONNECTION_H_

#include "net_common.h"
#include "net_tsqueue.h"
#include "net_message.h"

namespace olc {
namespace net {
    template <typename T>
    class connection: public std::enable_shared_from_this<connection<T>> {
    public:
        enum class owner {
            server,
            client
        };
    public:
        connection(owner parent, boost::asio::io_context& asio_context, boost::asio::ip::tcp::socket socket, ts_queue<owned_message<T>>& q_in)
            : m_asio_context(asio_context), m_socket(std::move(socket)), m_q_message_in(q_in)
             {
                m_n_owner_type = parent;
             }
        
        virtual ~connection() {}
        
        uint32_t get_id() const {
            return id;
        }

        // 服务端连接到客户端
        // uid是服务端给客户端assign的一个标记
        void connect_to_client(uint32_t uid = 0) {
            if(m_n_owner_type == owner::server) {
                if(m_socket.is_open()) {
                    id = uid;
                    read_header();
                } 
            }
        }

        // ConnectToServer直接用endpoint去连接， 然后就开始读头，读消息了
        void connect_to_server(boost::asio::ip::tcp::resolver::results_type const& endpoints) {
            if(m_n_owner_type == owner::client) {
                boost::asio::async_connect(m_socket, endpoints, 
                [this](boost::system::error_code ec, boost::asio::ip::tcp::endpoint endpoint) {
                    if(!ec) {
                        read_header();
                    }
                });
            }
        }

        // Disconnect的方法，向asio::context上面post一个socket.close()
        void disconnect() {
            if(is_connected()) {
                boost::asio::post(m_asio_context, [this](){
                    m_socket.close();
                });
            }
        }

        bool is_connected() {
            return m_socket.is_open();
        }

        void start_listening() {

        }

        void send(message<T> const& msg) {
            boost::asio::post(m_asio_context, [this, msg]() {
                bool b_writting_message = !m_q_message_out.empty();
                m_q_message_out.push_back(msg);
                if(!b_writting_message) {
                    write_header();
                }
            });
        }

    private:
        void write_header() {
            boost::asio::async_write(m_socket, boost::asio::buffer(&m_q_message_out.front().header, sizeof(message_header<T>)),
            [this](boost::system::error_code ec, std::size_t length) {
                if(!ec) {
                    if(m_q_message_out.front().body.size() > 0) {
                        write_body(); 
                    } else {
                        m_q_message_out.pop_front();
                        if(!m_q_message_out.empty()) {
                            write_header();
                        }
                    }
                } else {
                    std::cout << "[" << id << "] write header fail.\n";
                    m_socket.close();
                }
            });
        }

        void write_body() {
            boost::asio::async_write(m_socket, boost::asio::buffer(m_q_message_out.front().body.data(), m_q_message_out.front().body.size()),
            [this](boost::system::error_code ec, std::size_t length) {
                if(!ec) {
                    m_q_message_out.pop_front();
                    if(!m_q_message_out.empty()) {
                        write_header();
                    }
                } else {
                    std::cout << "[" << id <<  "] write body fail.\n";
                    m_socket.close();
                }
            });
        }

        void read_header() {
            boost::asio::async_read(m_socket, boost::asio::buffer(&m_msg_temporary_in.header, sizeof(message_header<T>)), 
            [this](boost::system::error_code ec, std::size_t length) {
                if(!ec) {
                    if(m_msg_temporary_in.header.size > 0) {
                        m_msg_temporary_in.body.resize(m_msg_temporary_in.header.size);
                        read_body();
                    } else {
                        add_to_incoming_message_queue();
                    }
                } else {
                    std::cout << "[" << id << "] read head fail\n";
                    m_socket.close();
                }
            });
        }

        void read_body() {
            boost::asio::async_read(m_socket, boost::asio::buffer(m_msg_temporary_in.body.data(), m_msg_temporary_in.body.size()), 
            [this](boost::system::error_code ec, std::size_t length) {
                if(!ec) {
                    add_to_incoming_message_queue();
                } else {
                    std::cout << "[" << id << "] read body fail.\n";
                    m_socket.close();
                }
            });
        }

        void add_to_incoming_message_queue() {
            if(m_n_owner_type == owner::server) {
                m_q_message_in.push_back({this->shared_from_this(), m_msg_temporary_in});
            } else {
                m_q_message_in.push_back({nullptr, m_msg_temporary_in});
            }

            read_header();
        }

    protected:
        boost::asio::ip::tcp::socket m_socket;
        boost::asio::io_context& m_asio_context;
        ts_queue<message<T>> m_q_message_out;
        
        // 收的时候收的是owned_message
		// This references the incoming queue of the parent object
        ts_queue<owned_message<T>>& m_q_message_in;
        // 临时消息，用于入队到m_q_message_in
        message<T> m_msg_temporary_in;

        owner m_n_owner_type = owner::server;
        // 服务端给客户端assign的ID
        uint32_t id = 0;
    };
}
}
#endif
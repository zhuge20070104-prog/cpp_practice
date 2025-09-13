#ifndef _FREDRIC_NET_SERVER_H_
#define  _FREDRIC_NET_SERVER_H_

#include "net_connection.h"

namespace olc {
namespace net {

    template <typename T>
    class server_interface {
    public:
        server_interface(uint16_t port):
            m_asio_acceptor(m_asio_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)) {}
        
        virtual ~server_interface() {
            stop();
        }

        bool start() {
            try {
                wait_for_client_connection();
                m_thread_context = std::thread([this]() {
                    m_asio_context.run();
                });
            }catch(std::exception& ex) {
                std::cerr << "[Server] Exception: " << ex.what() << "\n";
                return false;
            }

            std::cout << "[Server] started!\n";
            return true;
        }

        void stop() {
            m_asio_context.stop();
            if(m_thread_context.joinable()) {
                m_thread_context.join();
            }
            std::cout << "[Server] stopped!\n";
        }

        void wait_for_client_connection() {
            m_asio_acceptor.async_accept(
                [this](boost::system::error_code ec, boost::asio::ip::tcp::socket socket) {
                    if(!ec) {
                        std::cout << "[Server] new connection: " << socket.remote_endpoint() << "\n";
                        std::shared_ptr<connection<T>> new_conn = std::make_shared<connection<T>>(connection<T>::owner::server,
                        m_asio_context, std::move(socket), m_q_messages_in);

                        // 给用户的Server一个机会，可以deny connection
                        if(on_client_connect(new_conn)) {
                            m_deq_connections.push_back(std::move(new_conn));
                            m_deq_connections.back()->connect_to_client(this, n_id_counter++);
                            std::cout << "[" << m_deq_connections.back()->get_id() << "] connection approved\n";
                        } else {
                            std::cout << "[------] connection denied\n";
                        }
                    } else {
                        std::cout << "[Server] new connection error: " << ec.message() << "\n";
                    }

                    wait_for_client_connection();
                }
            );
        }

        // 向指定的客户发送消息
        void message_client(std::shared_ptr<connection<T>> client, message<T> const& msg) {
            if(client && client->is_connected()) {
                client->send(msg);
            } else {
                // 让用户的服务回调
                on_client_disconnect(client);
                client.reset();

                m_deq_connections.erase(
                std::remove(m_deq_connections.begin(), m_deq_connections.end(), client),
                m_deq_connections.end());
            }
        }

        // 向所有客户群发消息
        void message_all_clients(message<T> const& msg, std::shared_ptr<connection<T>> p_ignore_client = nullptr) {
            bool b_invalid_client_exists = false;
            for(auto& client: m_deq_connections) {
                if(client && client->is_connected()) {
                    if(client != p_ignore_client) {
                        client->send(msg);
                    }
                } else {
                    on_client_disconnect(client);
                    client.reset();
                    b_invalid_client_exists = true;
                }
            }

            if(b_invalid_client_exists) {
                m_deq_connections.erase(
                    std::remove(m_deq_connections.begin(), m_deq_connections.end(), nullptr),
                    m_deq_connections.end()
                );
            }
        }


        void on_client_validated(std::shared_ptr<connection<T>> client) {}


        void update(std::size_t n_max_messages = -1, bool b_wait = false) {
            if(b_wait) m_q_messages_in.wait();

            std::size_t n_message_count = 0;
            if(n_max_messages == -1) {
                n_max_messages = std::numeric_limits<std::size_t>::max();
            }
            while(n_message_count < n_max_messages && !m_q_messages_in.empty()) {
                auto msg = m_q_messages_in.pop_front();

                on_message(msg.remote, msg.msg);
                n_message_count++;
            }
        }
    protected:
        virtual bool on_client_connect(std::shared_ptr<connection<T>> client) {
            return false;
        } 

        virtual void on_client_disconnect(std::shared_ptr<connection<T>> client) {

        }

        virtual void on_message(std::shared_ptr<connection<T>> client, message<T>& msg) {

        }
    protected:
        ts_queue<owned_message<T>> m_q_messages_in;
        std::deque<std::shared_ptr<connection<T>>> m_deq_connections;
        boost::asio::io_context m_asio_context;
        std::thread m_thread_context;

        boost::asio::ip::tcp::acceptor m_asio_acceptor;

        uint32_t n_id_counter = 10000;
    };
} 
}
#endif
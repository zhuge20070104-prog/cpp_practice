#ifndef _FREDRIC_NET_CLIENT_H_
#define _FREDRIC_NET_CLIENT_H_

#include "net_common.h"
#include "net_connection.h"

namespace olc {
namespace net {

    template <typename T>
    class client_interface {
    public:
        client_interface() {}

        virtual ~client_interface() {
            disconnect();
        }
      
    public:
        bool connect(std::string const& host, uint16_t const port) {
            try {
                boost::asio::ip::tcp::resolver resolver(m_context);
                boost::asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(host, std::to_string(port));
                m_connection = std::make_unique<connection<T>>(connection<T>::owner::client, m_context, 
                    boost::asio::ip::tcp::socket(m_context), m_q_messages_in);
                m_connection->connect_to_server(endpoints);
                th_context = std::thread([this]() {
                    m_context.run();
                });

            }catch(std::exception& ex) {
                std::cout << "Clent exception: " << ex.what() << "\n";
                return false;
            }
            return true;
        }

        void disconnect() {
            if(is_connected()) {
                m_connection->disconnect();
            }

            m_context.stop();
            if(th_context.joinable()) {
                th_context.join();
            }

            m_connection.release();
        }

        bool is_connected() {
            if(m_connection) {
                return m_connection->is_connected();
            } else {
                return false;
            }
        }

    public:
        void send(message<T> const& msg) {
            if(is_connected()) {
                m_connection->send(msg);
            }
        }

        ts_queue<owned_message<T>>& incoming() {
            return m_q_messages_in;
        }
    protected:
        boost::asio::io_context m_context;
        std::thread th_context;
        std::unique_ptr<connection<T>> m_connection;
    
    private:
        ts_queue<owned_message<T>> m_q_messages_in;
    };
}
}
#endif
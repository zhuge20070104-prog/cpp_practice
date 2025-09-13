#include "net_server.h"
#include <string>
#include <iostream>


enum class custom_msg_types: uint32_t {
    server_accept,
    server_deny,
    server_ping,
    message_all,
    server_message
};

class custom_server: public olc::net::server_interface<custom_msg_types> {
public:
    custom_server(uint16_t n_port): olc::net::server_interface<custom_msg_types>(n_port) {}

protected:
        
        bool on_client_connect(std::shared_ptr<olc::net::connection<custom_msg_types>> client) {
            olc::net::message<custom_msg_types> msg;
            msg.header.id = custom_msg_types::server_accept;
            client->send(msg);
            return true;
        } 

        void on_client_disconnect(std::shared_ptr<olc::net::connection<custom_msg_types>> client) {
            std::cout << "removing client: [" << client->get_id() << "]\n";
        }

        void on_message(std::shared_ptr<olc::net::connection<custom_msg_types>> client,
        olc::net::message<custom_msg_types>& msg) {
            switch (msg.header.id) {
            case custom_msg_types::server_ping: {
                std::cout << "[" << client->get_id() << "]: server ping\n";
                client->send(msg);
            }
                break;
            
            case custom_msg_types::message_all: {
                std::cout << "[" << client->get_id() << "]: message all\n";
                olc::net::message<custom_msg_types> msg;
                msg.header.id = custom_msg_types::server_message;
                msg << client->get_id();
                message_all_clients(msg, client);
            }
                break;
            }
        }
};


int main(int argc, char* argv[]) {

    custom_server server(60000);
    server.start();
    
    while(true) {
        server.update(-1, true);
    }
    
    return EXIT_SUCCESS;
}
#include "net_client.h"
#include "file_log.h"
#include <string>
#include <iostream>
#include <vector>


enum class custom_msg_types: uint32_t {
    server_accept,
    server_deny,
    server_ping,
    message_all,
    server_message
};

class custom_client: public olc::net::client_interface<custom_msg_types> {
public:

    custom_client(): client_interface<custom_msg_types>(), log("."), b_quit(false) {}
    
    ~custom_client() {
        if(input_thread.joinable()) {
            input_thread.join();
        }
    }

    void process_input() {
        input_thread = std::thread([this]() {
            input_func();
        });
    }

    void process_incoming_messages() {
        while(!b_quit) {
            if(is_connected()) {
                if(!incoming().empty()) {
                    auto msg = incoming().pop_front().msg;
                    switch (msg.header.id) {
                    case custom_msg_types::server_accept:{
                        log << "server accepted connection\n";
                    }
                        break;
                    
                    case custom_msg_types::server_ping: {
                        std::chrono::system_clock::time_point time_now = std::chrono::system_clock::now();
                        std::chrono::system_clock::time_point time_then;
                        msg >> time_then;
                        log << "ping: " << std::chrono::duration<double>(time_now - time_then).count() << "\n";
                    }
                        break;
                    
                    case custom_msg_types::server_message: {
                        uint32_t client_id;
                        msg >> client_id;
                        log << "hello from [" << client_id << "]\n";
                    }
                        break;
                    }
                }    
            } else {
                log << "server down\n";
                b_quit = true;
            }
        }
    }

    void ping_server() {
        olc::net::message<custom_msg_types> msg;
        msg.header.id = custom_msg_types::server_ping;

        std::chrono::system_clock::time_point time_now = std::chrono::system_clock::now();
        msg << time_now;
        send(msg);
    }

    void message_all() {
        olc::net::message<custom_msg_types> msg;
        msg.header.id = custom_msg_types::message_all;
        send(msg); 
    }

private:
    void input_func() {
        while(!b_quit) {
      
            std::cout << "1. ping server\n"
                            << "2. message all\n"
                            << "3. quit\n";
            std::cout << "please enter your option: \n";
            int cmd;
            std::cin >> cmd;
            switch (cmd) {
            case 1:{
                ping_server();
            }
                break;
            case 2: {
                message_all();
            }
                break;
            case 3: {
                b_quit = true;
            } 
                break;
            
            default:
                break;
            }  
        }
    }

private:
    bool b_quit {false};
    std::thread input_thread;
    file_log log;
};


int main(int argc, char* argv[]) {
    custom_client c;
    c.connect("127.0.0.1", 60000);
    
    c.process_input();
    c.process_incoming_messages();
  
    std::cout << "Press any key to continue..." << std::endl;
    char ch;
    std::cin >> ch;

    return EXIT_SUCCESS;
}
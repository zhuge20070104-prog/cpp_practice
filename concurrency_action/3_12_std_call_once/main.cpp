#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
#include <functional>

// 连接信息
struct connection_info {};

// 数据包
struct data_packet {};

// 连接处理器，用来接收和发送数据包
struct connection_handle {
    void send_data(data_packet const&) {
        std::cout << "send data:\n";
    }

    data_packet receive_data() {
        std::cout << "receive data:\n";
        return data_packet();
    }
};

struct remote_connection_manager {
    connection_handle open(connection_info const&) {
        return connection_handle();
    }
} connection_manager;

class Server {
private:
    connection_info connection_details;
    connection_handle connection;
    std::once_flag connection_init_flag;

    void open_connection() {
        std::cout << "open connection, only calls for once..\n";
        connection = connection_manager.open(connection_details);
    }

public:
    Server(connection_info const& connection_details_):
        connection_details(connection_details_) {}

    void send_data(data_packet const& data) {
        std::call_once(connection_init_flag, &Server::open_connection, this);
        connection.send_data(data);
    } 

    data_packet receive_data() {
        std::call_once(connection_init_flag, &Server::open_connection, this);
        return connection.receive_data();
    }
};

// 一个类实例call一遍，两个类实例call两遍
int main(int argc, char* argv[]) {
    connection_info conn_info;
    Server server(conn_info);
    data_packet dp;
    std::vector<std::thread> send_threads;
    std::vector<std::thread> receive_threads;
    for(int i=0; i<5; ++i) {
        send_threads.push_back(std::thread(&Server::send_data, &server, std::cref(dp)));
        receive_threads.push_back(std::thread(&Server::receive_data, &server));
    }

    std::for_each(send_threads.begin(), send_threads.end(), std::mem_fn(&std::thread::join));
    std::for_each(receive_threads.begin(), receive_threads.end(), std::mem_fn(&std::thread::join));

    return EXIT_SUCCESS;
}
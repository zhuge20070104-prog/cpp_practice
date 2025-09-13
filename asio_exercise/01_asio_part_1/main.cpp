#include "boost/asio.hpp"
#include "boost/system/error_code.hpp"
#include <string>
#include <iostream>
#include <vector>

// 同步返回的两个问题
// 1. 我们不知道服务器什么时候给我们返回数据
// 2. 我们不知道服务器会给我们返回多大的数据，所以没办法预先确定buffer的大小
// 我们应该以异步方式获取HTTP 请求

int main(int argc, char* argv[]) {
    
    boost::system::error_code ec;
    boost::asio::io_context context;
    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::make_address("93.184.216.34", ec), 80);
    boost::asio::ip::tcp::socket socket(context);
    socket.connect(endpoint, ec);

    if(!ec) {
        std::cout << "Connected!" << std::endl;
    } else {
        std::cout << "Failed to connect to address: \n" << ec.message() << std::endl;
    }

    if(socket.is_open()) {
        std::string request = 
            "GET /index.html HTTP/1.1\r\n"
            "Host: example.com\r\n"
            "Connection: close\r\n\r\n";
        
            socket.write_some(boost::asio::buffer(request.data(), request.size()), ec);
            
             // 等待socket 有数据可读，否则可能读个空
            socket.wait(socket.wait_read);
            std::size_t bytes = socket.available();
            std::cout << "Bytes available: " << bytes << std::endl;

            if(bytes > 0) {
                std::vector<char> v_buffer(bytes);
                socket.read_some(boost::asio::buffer(v_buffer.data(), v_buffer.size()), ec);

                for(auto c: v_buffer) {
                    std::cout << c;
                }
            }
    }

   
    std::cout << "Press any key to continue..." << std::endl;
    char c;
    std::cin >> c;

    return EXIT_SUCCESS;
}
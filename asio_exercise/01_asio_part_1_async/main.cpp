#include "boost/asio.hpp"
#include "boost/system/error_code.hpp"
#include <string>
#include <iostream>
#include <vector>
#include <thread>


std::vector<char> v_buffer(20* 1024);

// 回调函数就是说搞一个读取标记在这儿，不是马上调用，
// 是数据到了的时候再开始回调
void grab_some_data(boost::asio::ip::tcp::socket& socket) {
    socket.async_read_some(boost::asio::buffer(v_buffer.data(), v_buffer.size()), 
        [&](boost::system::error_code ec, std::size_t length) {
            if(!ec) {
                std::cout << "\n\nRead " << length << "bytes\n\n";
                for(int i=0; i<length; ++i) {
                    std::cout << v_buffer[i];
                }
                grab_some_data(socket);
            }
        });
}


int main(int argc, char* argv[]) {
    
    boost::system::error_code ec;
    boost::asio::io_context context;

    // 给io_context一点work 做，免得他立即退出
    boost::asio::io_context::work idle_work(context);

    std::thread th_context([&](){
        context.run();
    });


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
            grab_some_data(socket);
    }

    th_context.join();
    std::cout << "Press any key to continue..." << std::endl;
    char c;
    std::cin >> c;

    return EXIT_SUCCESS;
}
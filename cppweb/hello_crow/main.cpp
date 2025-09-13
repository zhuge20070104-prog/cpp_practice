#include "crow_all.h"

int main(int argc, char* argv[]) {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/") (
        []() {
            return "<div><h1>Hello, Crow.</h1></div>";       
        }
    );

    char* port = getenv("PORT");
    uint16_t i_port = static_cast<uint16_t>(port != nullptr? std::stoi(port): 18080);
    std::cout << "PORT = " << i_port << std::endl;
    app.port(i_port).multithreaded().run();
    return EXIT_SUCCESS;
}
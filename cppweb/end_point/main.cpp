#include "crow_all.h"



int main(int argc, char* argv[]) {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/rest_test").methods(crow::HTTPMethod::Post,
        crow::HTTPMethod::Get, crow::HTTPMethod::Put)(
        [](crow::request const& req, crow::response& res) {
            std::string method = crow::method_name(req.method);
            res.set_header("Content-Type", "text/plain");
            res.write(method + "    rest_test");
            res.end();
        }
    );

    char* port = getenv("PORT");
    uint16_t i_port = static_cast<uint16_t>(port != nullptr? std::stoi(port): 18080);
    std::cout << "PORT = " << i_port << std::endl;
    app.port(i_port).multithreaded().run();
    return EXIT_SUCCESS;
}
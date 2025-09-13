#include "crow_all.h"
#include <fstream>
#include <sstream>


int main(int argc, char* argv[]) {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/") (
        [](crow::request const& req, crow::response& res) {
            std::ifstream in("../public/index.html", std::ifstream::in);
            if(in) {
                std::ostringstream contents;
                contents << in.rdbuf();
                in.close();
                res.write(contents.str());
            } else {
                res.write("Not found");
            }
            res.end();   
        }
    );

    char* port = getenv("PORT");
    uint16_t i_port = static_cast<uint16_t>(port != nullptr? std::stoi(port): 18080);
    std::cout << "PORT = " << i_port << std::endl;
    app.port(i_port).multithreaded().run();
    return EXIT_SUCCESS;
}
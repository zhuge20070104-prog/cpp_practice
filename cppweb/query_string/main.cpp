#include "crow_all.h"

int main(int argc, char* argv[]) {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/") (
        []() {
            return "<div><h1>Hello, Crow.</h1></div>";       
        }
    );

    CROW_ROUTE(app, "/query")(
        [](crow::request const& req, crow::response& res) {
            auto first_name = req.url_params.get("firstname");
            auto last_name = req.url_params.get("lastname");
            std::ostringstream os;
            os << "Hello " << (first_name? first_name: "") <<
                "   " << (last_name? last_name: "") << std::endl;
            res.set_header("Content-Type", "text/plain");
            res.write(os.str());
            res.end();   
        }
    );

    char* port = getenv("PORT");
    uint16_t i_port = static_cast<uint16_t>(port != nullptr? std::stoi(port): 18080);
    std::cout << "PORT = " << i_port << std::endl;
    app.port(i_port).multithreaded().run();
    return EXIT_SUCCESS;
}
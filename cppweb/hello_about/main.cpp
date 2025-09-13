#include "crow_all.h"
#include <fstream>
#include <sstream>
#include <string>

void send_file(crow::response& res, std::string file_name, std::string content_type) {
    std::ifstream in("../public/" + file_name, std::ifstream::in);
        if(in) {
            std::ostringstream contents;
            contents << in.rdbuf();
            in.close();
            res.set_header("Content-Type", content_type);
            res.write(contents.str());
        } else {
            res.code = 404;
            res.write("Not found");
        }
        res.end();   
}

void send_html(crow::response& res, std::string file_name) {
    send_file(res, file_name + ".html", "text/html");
}


void send_image(crow::response& res, std::string file_name) {
    send_file(res, "images/" + file_name, "image/jpeg");
}

void send_script(crow::response& res, std::string file_name) {
    send_file(res, "scripts/" + file_name, "text/javascript");
}

void send_style(crow::response& res, std::string file_name) {
    send_file(res, "styles/" + file_name, "text/css");
}


int main(int argc, char* argv[]) {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/styles/<string>") (
        [](crow::request const& req, crow::response& res, std::string file_name) {
            send_style(res, file_name);
        }
    );

    CROW_ROUTE(app, "/scripts/<string>") (
        [](crow::request const& req, crow::response& res, std::string file_name) {
            send_script(res, file_name);
        }
    );

    CROW_ROUTE(app, "/images/<string>") (
        [](crow::request const& req, crow::response& res, std::string file_name) {
            send_image(res, file_name);
        }
    );

    CROW_ROUTE(app, "/about") (
        [](crow::request const& req, crow::response& res) {
            send_html(res, "about");
        }
    );

    

    char* port = getenv("PORT");
    uint16_t i_port = static_cast<uint16_t>(port != nullptr? std::stoi(port): 18080);
    std::cout << "PORT = " << i_port << std::endl;
    app.port(i_port).multithreaded().run();
    return EXIT_SUCCESS;
}
#include "crow_all.h"
#include "sqllite_op.h"
#include "json.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <mutex>
#include <unordered_set>


using ordered_json = nlohmann::ordered_json;

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

std::string get_view(std::string const& file_name, crow::mustache::context& ctx ) {
    return crow::mustache::load("../public/" + file_name + ".html").render(ctx);
}

int main(int argc, char* argv[]) {
    std::mutex mtx;
    std::unordered_set<crow::websocket::connection*> users;

    crow::SimpleApp app;
    // mustache需要这一句，没有set_base, mustache不工作
    crow::mustache::set_base(".");

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

    CROW_ROUTE(app, "/") (
        [](crow::request const& req, crow::response& res) {
            send_html(res, "index");
        }
    );

    CROW_ROUTE(app, "/ws").websocket()
    .onopen(
        [&](crow::websocket::connection& conn) {
            std::lock_guard<std::mutex> _(mtx);
            std::cout << "Opened" << std::endl;
            users.insert(&conn);
        }
    ).onclose(
        [&](crow::websocket::connection& conn, std::string const& reason) {
            std::lock_guard<std::mutex> _(mtx);
            std::cout << "Closed" << std::endl;
            users.erase(&conn);
        }
    ).onmessage(
        [&](crow::websocket::connection& /*conn*/, std::string const& data, bool is_binary) {
            std::lock_guard<std::mutex> _(mtx);
            std::cout << "Send Message: " << data << std::endl;
            for(auto user: users) {
                if(is_binary) {
                    user->send_binary(data);
                } else {
                    user->send_text(data);
                }
            }
        }        
    );

    CROW_ROUTE(app, "/chat")(
        [](crow::request const& req, crow::response& res) {
            send_html(res, "chat");
        }
    );

    

    

    char* port = getenv("PORT");
    uint16_t i_port = static_cast<uint16_t>(port != nullptr? std::stoi(port): 18080);
    std::cout << "PORT = " << i_port << std::endl;
    app.port(i_port).multithreaded().run();
    return EXIT_SUCCESS;
}
#include "crow_all.h"
#include "sqllite_op.h"
#include "json.hpp"
#include <fstream>
#include <sstream>
#include <string>

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
    crow::SimpleApp app;
    // mustache需要这一句，没有set_base, mustache不工作
    crow::mustache::set_base(".");
    std::string db_name {"../test.db"};

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

    CROW_ROUTE(app, "/contacts")(
        [&]() {
            SQLiteOp sqlite_op(db_name);
            std::string query_str = "SELECT * FROM CONTACT LIMIT 4 OFFSET 4";
            sqlite_op.Open();
            auto results = sqlite_op.Query(query_str);
            crow::json::wvalue dto;
            std::vector<crow::json::rvalue> contacts;
            contacts.reserve(4);
            for(auto const& result: results) {
                ordered_json js_res;
                for(auto const& entry: result) {
                    js_res[entry.first] = entry.second;
                }
                contacts.push_back(crow::json::load(js_res.dump()));
            }
            dto["contacts"] = contacts;
            return get_view("contacts", dto);
        }
    );

    CROW_ROUTE(app, "/contact/<string>")(
        [&](std::string email) {
            SQLiteOp sqlite_op(db_name);
            std::string query_str = "SELECT * FROM CONTACT where email='" + email + "'";
            sqlite_op.Open();
            auto results = sqlite_op.Query(query_str);
            crow::json::wvalue dto;
            std::vector<crow::json::rvalue> contacts;
            contacts.reserve(4);
            for(auto const& result: results) {
                ordered_json js_res;
                for(auto const& entry: result) {
                    js_res[entry.first] = entry.second;
                }
                contacts.push_back(crow::json::load(js_res.dump()));
            }
            dto["contact"] = contacts;
            return get_view("contact", dto);
        }
    );

    

    char* port = getenv("PORT");
    uint16_t i_port = static_cast<uint16_t>(port != nullptr? std::stoi(port): 18080);
    std::cout << "PORT = " << i_port << std::endl;
    app.port(i_port).multithreaded().run();
    return EXIT_SUCCESS;
}
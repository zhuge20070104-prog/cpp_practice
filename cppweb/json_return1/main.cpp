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
        [&](crow::request const& req, crow::response& res) {
            SQLiteOp sqlite_op(db_name);
            auto skip_val = req.url_params.get("skip");
            auto limit_val = req.url_params.get("limit");

            auto skip = skip_val ? skip_val: "0";
            auto limit = limit_val? limit_val: "10";
            
            std::string query_str = "SELECT * FROM CONTACT LIMIT " + std::string(limit) + " OFFSET " + skip;
            sqlite_op.Open();
            auto results = sqlite_op.Query(query_str);
            ordered_json js_results;
            js_results["contacts"] = ordered_json::array();            
            for(auto const& result: results) {
                ordered_json js_res;
                for(auto const& entry: result) {
                    js_res[entry.first] = entry.second;
                }
                js_results["contacts"].push_back(js_res);
            }

            res.set_header("Content-Type", "application/json");
            res.write(js_results.dump(4));
            res.end();
        }
    );

    char* port = getenv("PORT");
    uint16_t i_port = static_cast<uint16_t>(port != nullptr? std::stoi(port): 18080);
    std::cout << "PORT = " << i_port << std::endl;
    app.port(i_port).multithreaded().run();
    return EXIT_SUCCESS;
}
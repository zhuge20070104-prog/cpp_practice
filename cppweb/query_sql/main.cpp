#include "crow_all.h"
#include "json.hpp"
#include "sqllite_op.h"
#include <iostream>
#include <fstream>
#include <sstream>

using ordered_json = nlohmann::ordered_json;

int main(int argc, char* argv[]) {
    crow::SimpleApp app;
    std::string db_name = "../test.db";

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

    CROW_ROUTE(app, "/contacts")(
        [&]() {
            SQLiteOp sqlite_op(db_name);
            sqlite_op.Open();
            std::string query_str = "SELECT * FROM CONTACT LIMIT 4 OFFSET 4";
            auto results = sqlite_op.Query(query_str);
            ordered_json js_results;
            for(auto const& result: results) {
                ordered_json js_res;
                for(auto const& entry: result) {
                    js_res[entry.first] = entry.second;
                }
                js_results.push_back(js_res);
            }
            return crow::response(js_results.dump(4));
        }
    );

    char* port = getenv("PORT");
    uint16_t i_port = static_cast<uint16_t>(port != nullptr? std::stoi(port): 18080);
    std::cout << "PORT = " << i_port << std::endl;
    app.port(i_port).multithreaded().run();
    return EXIT_SUCCESS;
}

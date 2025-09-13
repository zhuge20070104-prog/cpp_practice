#include "http_server.hpp"
#include <sstream>
#include "json.hpp"

using json = nlohmann::json;

int main(int argc, char* argv[])
{
    // Check command line arguments.
    if (argc != 5)
    {
        std::cerr <<
            "Usage: http-server-async <address> <port> <doc_root> <threads>\n" <<
            "Example:\n" <<
            "    http-server-async 0.0.0.0 8080 . 1\n";
        return EXIT_FAILURE;
    }
    
    std::string host = argv[1];
    std::string port = argv[2];
    std::string doc_root = argv[3];
    int thread = std::atoi(argv[4]);

    Server s(host, port, doc_root, thread);

    REGIST_REQ(http::verb::get, "/",  [](ReqType& req, SendType& send, std::vector<std::string> const&  params) {
           MAKE_REQUEST_RESP(req_resp_html, "text/html", http::status::ok, req);
            return send(req_resp_html("Hello World!"));
    });

    REGIST_REQ(http::verb::post, "/plus",  [](ReqType& req, SendType& send, std::vector<std::string> const& params) {
            MAKE_REQUEST_RESP(req_resp_json, "application/json", http::status::ok, req);
            std::stringstream body_ss;
            body_ss << req.body();
            auto js_params = json::parse(body_ss.str());
            int x = js_params["x"].get<int>();
            int y = js_params["y"].get<int>();
            int sum = x + y;
            json result;
            result["sum"] = sum;
            std::string res = result.dump(4);
            return send(req_resp_json(res.data()));
    });

    REGIST_REQ(http::verb::get, R"(/api/pingpong/(.*))",  [](ReqType& req, SendType& send, std::vector<std::string> const& params) {
            MAKE_REQUEST_RESP(req_resp_html, "text/html", http::status::ok, req);
            std::stringstream ss;
            ss << params[0] << " " << "pong";
            return send(req_resp_html(ss.str()));
    });

    REGIST_REQ(http::verb::get, R"(/query)",  [](ReqType& req, SendType& send, std::vector<std::string> const& params) {
            MAKE_REQUEST_RESP(req_resp_html, "text/html", http::status::ok, req);
            std::stringstream ss;
            ss << params[0] << " " << params[1] << " " << "Query";
            return send(req_resp_html(ss.str()));
    });


    s.run();    
    return EXIT_SUCCESS;
}
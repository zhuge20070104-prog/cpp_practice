#ifndef _FREDRIC_HTTP_SERVER_HPP_
#define _FREDRIC_HTTP_SERVER_HPP_
//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

//------------------------------------------------------------------------------
//
// Example: HTTP server, asynchronous
//
//------------------------------------------------------------------------------
#include "http_common.h"
#include <boost/functional/hash.hpp>
#include <map>
#include <boost/algorithm/string.hpp>
#include <regex>


#define  MAKE_REQUEST_RESP(request_name,  content_type_, status_code, request)    auto const request_name = \
    [&request](beast::string_view resp_content) \
    {   \
        http::response<http::string_body> res{status_code, request.version()}; \
        res.set(http::field::server, BOOST_BEAST_VERSION_STRING); \
        res.set(http::field::content_type, content_type_); \
        res.keep_alive(request.keep_alive()); \
        res.body() = std::string(resp_content); \
        res.prepare_payload(); \
        return res; \
    }; \


struct RequestKey {
    http::verb method;
    std::string target;

    bool operator<(RequestKey const& other) const {
        return (int)method < (int)(other.method) && target < other.target;
    }
};

template<
    class Body,
    class Send>
struct Function {

    Function(std::string const& long_target_,    
        std::function<void(http::request<Body>&, Send&, std::vector<std::string> const&)> func_):
         long_match_regex(long_target_), callback_func(func_) {

    }
    std::string long_match_regex;
    std::function<void(http::request<Body>&, Send&, std::vector<std::string> const&)> callback_func; 
    std::vector<std::string> params;
    bool is_reg{false};

    bool operator<(Function<Body, Send> const& other) const {
        return long_match_regex < other.long_match_regex;
    }
};

struct TargetResult {
    std::string short_target;
    std::string long_target;
    bool is_reg {false};
    bool is_query {false};
};


template<
    class Body,
    class Send>
struct RequestHandler {
    
    static std::map<RequestKey,  std::set<Function<Body, Send>> > callback_map;
    /**
     * NOTE: 带问号的URL需要单独处理，去掉问号后面的，
     * 问号 前面的 作为 target 和 long_match_regex
     * 
     * RequestKey 里面保存 一级path, 例如, 
     * http::verb::get   api
     *
     *  long_match_regex 里面保存 二级path，例如，
     *  api/(.*)/(.*) 
     * 
     *  1. api/(.*)/(.*) 
     *  2. api?a=b&c=d  
     *  3. api   --> find 处理的是第三种情况
     * 
     * 
     * struct Funcion {
     *      std::string long_match_regex;
     *      std::function<void(http::request<Body>&, Send&)> callback_func;  
     * };
     * 
     * std::map<RequestKey, std::set<Function>>
    */

   static void preprocess_target(std::string const& target, TargetResult& tar_result) {
            tar_result.short_target = target;
            tar_result.long_target = target;
            if(target.find("?") != std::string::npos)  {
                tar_result.short_target = std::string(target.begin() ,  target.begin() + target.find("?"));
                tar_result.long_target =  tar_result.short_target;
                tar_result.is_query = true;
            } else if(target.find(R"((.*))") != std::string::npos) {
                tar_result.short_target = boost::algorithm::replace_all_copy(target, R"(/(.*))", "");
                tar_result.long_target = target;
                tar_result.is_reg = true;
            }
   }

    static void register_request(RequestKey const& key, 
        std::function<void(http::request<Body>&, Send&, std::vector<std::string> const&)> const& callback)  {
            std::string target = key.target;
            TargetResult tar_result; 
            preprocess_target(target, tar_result);

            RequestKey fixed_key = RequestKey{key.method, tar_result.short_target};

            if(callback_map.find(fixed_key) == callback_map.end()) {
                callback_map[fixed_key] = std::set<Function<Body, Send>>();
            }

            Function<Body, Send> func_{tar_result.long_target, callback};
            func_.is_reg = tar_result.is_reg;
            callback_map[fixed_key].insert(func_);
    }
    
    static void handle_request(
        beast::string_view doc_root,
        http::request<Body>&& req,
        Send& send) {

        // 处理 target 情况
        // 1. api/(.*)/(.*) 
        // 2. api?a=b&c=d  
        // 3. api   --> find 处理的是第三种情况

        /** 
         * NOTE: 带问号的URL需要单独处理，去掉问号后面的，
         *  问号 前面的 作为 target 和 long_match_regex
         *
         * api/pingpong 短的， api/pingpong/(.*)
         * 例如 api/pingpong/hello
         * 1. 先找 api/pingpong，看有没有, {short_target}
         * 2. 再根据正则表达式匹配，  {long_target.match(req.target())}
        */

        auto target = std::string(req.target());

        TargetResult tar_result; 
        preprocess_target(target, tar_result);
       
        RequestKey req_key{req.method(),  tar_result.short_target};
        bool has_matched {false};

        if(callback_map.find(req_key) != callback_map.end()) {
            auto& callback_set = callback_map[req_key];
            for(auto& callback_func: callback_set) {
                auto match_regex = callback_func.long_match_regex;
                auto func = callback_func.callback_func;
                auto params = callback_func.params;
                auto is_reg = callback_func.is_reg;
                std::string actual_req_target = target;
                // 处理正则表达式匹配, /api/pingpong/(.*)/(.*)
                if(is_reg) {
                    std::regex rgx(match_regex);
                    std::smatch matches;
                    
                    params.clear();
                    if(std::regex_search(actual_req_target, matches, rgx)) {
                        std::cout << "Match found\n";
                        for (size_t i = 0; i < matches.size(); ++i) {
                            // 第一个match 是整个字符串，跳过
                            if(i!=0) {
                                params.push_back(matches[i].str());
                            }
                        }
                        func(req, send, params);
                        has_matched = true;
                        break;
                    }   // 处理问号匹配  /query?a=b&c=d
                } else if(tar_result.is_query) {
                    params.clear();
                    if(match_regex == tar_result.long_target) {
                        std::cout << "Match found\n";
                        std::vector<std::string> result;
                        boost::split(result, actual_req_target, boost::is_any_of("?"));
                        std::string params_str = result[1];
                        boost::split(params, params_str, boost::is_any_of("&"));
                        func(req, send, params);
                        has_matched = true;
                        break;
                    }   // 处理普通匹配 /api/aa 
                } else {
                    if(match_regex == actual_req_target) {
                        std::cout << "Match found\n";
                        func(req, send, params);
                        has_matched = true;
                        break;
                    }
                }
            }
        }
        
        // 都没匹配到，返回默认not found 页面
        if(!has_matched) {
            std::cout << "Match not found\n";
            MAKE_REQUEST_RESP(req_resp_not_found, "text/html", http::status::not_found, req);
            return send(req_resp_not_found("The resource '" + std::string(req.target()) + "' was not found."));
        } 
    }
};

template<
    class Body,
    class Send>
 std::map<RequestKey, std::set<Function<Body, Send>> >  RequestHandler<Body, Send>::callback_map;



//------------------------------------------------------------------------------

// Handles an HTTP server connection
class session : public std::enable_shared_from_this<session>
{
public:
    // This is the C++11 equivalent of a generic lambda.
    // The function object is used to send an HTTP message.
    struct send_lambda
    {
        session& self_;

        explicit
        send_lambda(session& self)
            : self_(self)
        {
        }

        template<bool isRequest, class Body, class Fields>
        void
        operator()(http::message<isRequest, Body, Fields>&& msg) const
        {
            // The lifetime of the message has to extend
            // for the duration of the async operation so
            // we use a shared_ptr to manage it.
            auto sp = std::make_shared<
                http::message<isRequest, Body, Fields>>(std::move(msg));

            // Store a type-erased version of the shared
            // pointer in the class to keep it alive.
            self_.res_ = sp;

            // Write the response
            http::async_write(
                self_.stream_,
                *sp,
                beast::bind_front_handler(
                    &session::on_write,
                    self_.shared_from_this(),
                    sp->need_eof()));
        }
    };

private:
    beast::tcp_stream stream_;
    beast::flat_buffer buffer_;
    std::shared_ptr<std::string const> doc_root_;
    http::request<http::string_body> req_;
    std::shared_ptr<void> res_;
    send_lambda lambda_;

public:
    // Take ownership of the stream
    session(
        tcp::socket&& socket,
        std::shared_ptr<std::string const> const& doc_root)
        : stream_(std::move(socket))
        , doc_root_(doc_root)
        , lambda_(*this)
    {
    }

    // Start the asynchronous operation
    void
    run()
    {
        // We need to be executing within a strand to perform async operations
        // on the I/O objects in this session. Although not strictly necessary
        // for single-threaded contexts, this example code is written to be
        // thread-safe by default.
        net::dispatch(stream_.get_executor(),
                      beast::bind_front_handler(
                          &session::do_read,
                          shared_from_this()));
    }

    void
    do_read()
    {
        // Make the request empty before reading,
        // otherwise the operation behavior is undefined.
        req_ = {};

        // Set the timeout.
        stream_.expires_after(std::chrono::seconds(30));

        // Read a request
        http::async_read(stream_, buffer_, req_,
            beast::bind_front_handler(
                &session::on_read,
                shared_from_this()));
    }

    void
    on_read(
        beast::error_code ec,
        std::size_t bytes_transferred)
    {
        boost::ignore_unused(bytes_transferred);

        // This means they closed the connection
        if(ec == http::error::end_of_stream)
            return do_close();

        if(ec)
            return fail(ec, "read");

        // Send the response
        RequestHandler<http::string_body, send_lambda>::handle_request(*doc_root_, std::move(req_), lambda_);
    }

    void
    on_write(
        bool close,
        beast::error_code ec,
        std::size_t bytes_transferred)
    {
        boost::ignore_unused(bytes_transferred);

        if(ec)
            return fail(ec, "write");

        if(close)
        {
            // This means we should close the connection, usually because
            // the response indicated the "Connection: close" semantic.
            return do_close();
        }

        // We're done with the response so delete it
        res_ = nullptr;

        // Read another request
        do_read();
    }

    void
    do_close()
    {
        // Send a TCP shutdown
        beast::error_code ec;
        stream_.socket().shutdown(tcp::socket::shutdown_send, ec);

        // At this point the connection is closed gracefully
    }
};

//------------------------------------------------------------------------------

// Accepts incoming connections and launches the sessions
class listener : public std::enable_shared_from_this<listener>
{
    net::io_context& ioc_;
    tcp::acceptor acceptor_;
    std::shared_ptr<std::string const> doc_root_;

public:
    listener(
        net::io_context& ioc,
        tcp::endpoint endpoint,
        std::shared_ptr<std::string const> const& doc_root)
        : ioc_(ioc)
        , acceptor_(net::make_strand(ioc))
        , doc_root_(doc_root)
    {
        beast::error_code ec;

        // Open the acceptor
        acceptor_.open(endpoint.protocol(), ec);
        if(ec)
        {
            fail(ec, "open");
            return;
        }

        // Allow address reuse
        acceptor_.set_option(net::socket_base::reuse_address(true), ec);
        if(ec)
        {
            fail(ec, "set_option");
            return;
        }

        // Bind to the server address
        acceptor_.bind(endpoint, ec);
        if(ec)
        {
            fail(ec, "bind");
            return;
        }

        // Start listening for connections
        acceptor_.listen(
            net::socket_base::max_listen_connections, ec);
        if(ec)
        {
            fail(ec, "listen");
            return;
        }
    }

    // Start accepting incoming connections
    void
    run()
    {
        do_accept();
    }

private:
    void
    do_accept()
    {
        // The new connection gets its own strand
        acceptor_.async_accept(
            net::make_strand(ioc_),
            beast::bind_front_handler(
                &listener::on_accept,
                shared_from_this()));
    }

    void
    on_accept(beast::error_code ec, tcp::socket socket)
    {
        if(ec)
        {
            fail(ec, "accept");
        }
        else
        {
            // Create the session and run it
            std::make_shared<session>(
                std::move(socket),
                doc_root_)->run();
        }

        // Accept another connection
        do_accept();
    }
};

//------------------------------------------------------------------------------


struct Server {
    Server(std::string const& host_, std::string const& port_, std::string const& doc_root_, int threads_)
        : ioc{threads_}, host(host_), port(static_cast<unsigned short>(std::atoi(port_.data()))),
        doc_root(doc_root_), threads(std::max<int>(1, threads_))  {

    }

    void run() {
        auto address = net::ip::make_address(host);
        auto doc_root_inner = std::make_shared<std::string>(doc_root.data());
    
        // Create and launch a listening port
        std::make_shared<listener>(
            ioc,
            tcp::endpoint{address, port},
            doc_root_inner)->run();

        // Run the I/O service on the requested number of threads
        std::vector<std::thread> v;
        v.reserve(threads - 1);
        for(auto i = threads - 1; i > 0; --i)
            v.emplace_back(
            [this]
            {
                ioc.run();
            });
        ioc.run();
    }

private:
    net::io_context ioc;
    std::string host;
    unsigned short port;
    std::string doc_root;
    int threads;
};

#define  HTTPRequestHandler  RequestHandler<http::string_body, session::send_lambda>
#define  REGIST_REQ(method, target, func)     HTTPRequestHandler::register_request({method, target}, func)

#define  ReqType http::request<http::string_body>
#define  SendType session::send_lambda
#endif
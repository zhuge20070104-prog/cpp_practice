#ifndef _HTTP_CLIENT_HPP_
#define _HTTP_CLIENT_HPP_

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
// Example: HTTP client, asynchronous
//
//------------------------------------------------------------------------------

#include "http_common.h"
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/strand.hpp>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <string>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

//------------------------------------------------------------------------------

// Report a failure


// Performs an HTTP GET and prints the response
template <typename Req, typename Res>
class session : public std::enable_shared_from_this<session<Req, Res>>
{
    tcp::resolver resolver_;
    beast::tcp_stream stream_;
    beast::flat_buffer buffer_; // (Must persist between reads)
    http::request<Req>& req_;
    http::response<Res>& res_;

public:
    // Objects are constructed with a strand to
    // ensure that handlers do not execute concurrently.
   
    explicit
    session(net::io_context& ioc, http::request<Req>& req,  http::response<Res>& res)
        : resolver_(net::make_strand(ioc))
        , stream_(net::make_strand(ioc)),
        req_(req),
        res_(res)
    {
    }

    http::request<Req>& get_request() {
        return req_;
    } 

    http::response<Res>& get_response() {
        return res_;
    }

    // Start the asynchronous operation
    void
    run(
        char const* host,
        char const* port,
        int version)
    {
        // Look up the domain name
        resolver_.async_resolve(
            host,
            port,
            beast::bind_front_handler(
                &session::on_resolve,
                this->shared_from_this()));
    }

    void
    on_resolve(
        beast::error_code ec,
        tcp::resolver::results_type results)
    {
        if(ec)
            return fail(ec, "resolve");

        // Set a timeout on the operation
        stream_.expires_after(std::chrono::seconds(30));

        // Make the connection on the IP address we get from a lookup
        stream_.async_connect(
            results,
            beast::bind_front_handler(
                &session::on_connect,
                this->shared_from_this()));
    }

    void
    on_connect(beast::error_code ec, tcp::resolver::results_type::endpoint_type)
    {
        if(ec)
            return fail(ec, "connect");

        // Set a timeout on the operation
        stream_.expires_after(std::chrono::seconds(30));

        // Send the HTTP request to the remote host
        http::async_write(stream_, req_,
            beast::bind_front_handler(
                &session::on_write,
                this->shared_from_this()));
    }

    void
    on_write(
        beast::error_code ec,
        std::size_t bytes_transferred)
    {
        boost::ignore_unused(bytes_transferred);

        if(ec)
            return fail(ec, "write");
        
        // Receive the HTTP response
        http::async_read(stream_, buffer_, res_,
            beast::bind_front_handler(
                &session::on_read,
                this->shared_from_this()));
    }

    void
    on_read(
        beast::error_code ec,
        std::size_t bytes_transferred)
    {
        boost::ignore_unused(bytes_transferred);

        if(ec)
            return fail(ec, "read");

        // Write the message to standard out
        // std::cout << res_ << std::endl;

        // Gracefully close the socket
        stream_.socket().shutdown(tcp::socket::shutdown_both, ec);

        // not_connected happens sometimes so don't bother reporting it.
        if(ec && ec != beast::errc::not_connected)
            return fail(ec, "shutdown");

        // If we get here then the connection is closed gracefully
    }
};

template <typename Req, typename Res>
struct ReqContext {
    http::request<Req> req;
    http::response<Res> res;

    ReqContext(http::request<Req> const& req_, http::response<Res> const&  res_): req(req_), res(res_) {} 
};

template <typename Req, typename Res>
struct ClientSession {
    net::io_context& ioc;
    http::request<Req>& req;
    http::response<Res>& res;

    std::string host;
    std::string port;
    std::string target;

    ClientSession(net::io_context& ioc_, http::request<Req>& req_,
    http::response<Res>& res_,
    std::string host_,
    std::string port_,
    std::string target_): ioc(ioc_), req(req_), res(res_), host(host_), port(port_), target(target_) {}

    void Get() {
        req.version(11);
        req.method(http::verb::get);
        req.target(target);
        req.set(http::field::host, host);
        req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
        std::make_shared<session<Req, Res>>(ioc, req, res)->run(host.data(), port.data(), 11);
        ioc.run();
        // Run the I/O service. The call will return when
        // the get operation is complete.
    }
    
    void Post(std::string const& body) {
        req.version(11);
        req.method(http::verb::post);
        req.target(target);
        req.set(http::field::host, host);
        req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
        req.set(http::field::content_type, "application/json");
        req.body() =  body.data();
        req.prepare_payload();
        std::make_shared<session<Req, Res>>(ioc, req, res)->run(host.data(), port.data(), 11);
        ioc.run();
    }
};

template <typename Req, typename Res>
ReqContext<Req, Res> GetRequest(std::string const& host, std::string const& port, std::string const& target) {
    net::io_context ioc;
    http::request<Req> req;
    http::response<Res> res;
    ClientSession<Req, Res>  client(ioc, req, res, host, port, target);
    client.Get();
    return ReqContext<Req ,  Res>(req, res);
}

template <typename Req, typename Res>
ReqContext<Req, Res> PostRequest(std::string const& host, std::string const& port, std::string const& target, 
    std::string const& body) {
    net::io_context ioc;
    http::request<Req> req;
    http::response<Res> res;
    ClientSession<Req, Res>  client(ioc, req, res, host, port, target);
    client.Post(body);
    return ReqContext<Req ,  Res>(req, res);
}

#define GET GetRequest<http::empty_body, http::string_body>
#define POST PostRequest<http::string_body, http::string_body>

#endif
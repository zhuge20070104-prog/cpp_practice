#ifndef _FREDRIC_VIRTUAL_PROXY_HPP_
#define _FREDRIC_VIRTUAL_PROXY_HPP_
#include <string>
#include <iostream>
#include <memory>
#include <functional>

#include "log.h"
#include "http_client.hpp"

struct Pinable {
    virtual std::string ping(std::string const& message) const = 0;
};

struct Pong: Pinable {
    std::string ping(std::string const& message) const override {
        return message + " pong";
    }
};

struct RemotePong: Pinable {
    std::string ping(std::string const& message) const override  {
        auto res = GET("127.0.0.1", "8080", "/api/pingpong/" + message);
        if(res.res.result_int() != 200) {
            B_LOG(error) << "Request failed\n";
            return "";
        }

        return std::string(res.res.body());
    }
};


void try_it(Pinable const& pin) {
      std::cout << pin.ping("hello") << "\n";
}
#endif
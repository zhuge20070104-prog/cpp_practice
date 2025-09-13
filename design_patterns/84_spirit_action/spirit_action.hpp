#ifndef _FREDRIC_SPIRIT_ACTION_HPP_
#define _FREDRIC_SPIRIT_ACTION_HPP_
#include <string>
#include <iostream>
#include <memory>
#include <functional>
#include <vector>
#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>

#include "log.h"

namespace client {
    namespace qi = boost::spirit::qi;

    // A plain function
    void print(int const& i) {
        B_LOG(info) << i << "\n";
    }

    // A member function
    struct Writer {
        void print(int const& i) const {
            B_LOG(info) << i << "\n";
        }
    };

    // A function object
    struct PrintAction {
        void operator()(int const& i, qi::unused_type, qi::unused_type) const {
            B_LOG(info) << i << "\n";
        }
    };
}


#endif
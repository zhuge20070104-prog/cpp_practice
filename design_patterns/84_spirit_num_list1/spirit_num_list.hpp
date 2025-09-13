#ifndef _FREDRIC_SPIRIT_NUM_LIST_HPP_
#define _FREDRIC_SPIRIT_NUM_LIST_HPP_
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
    namespace ascii = boost::spirit::ascii;

    template <typename Iterator>
    bool parse_numbers(Iterator first, Iterator last) {
        using qi::double_;
        using qi::phrase_parse;
        using ascii::space;

        bool r = phrase_parse(
            first,
            last,
            // Start expression
            double_ >> *(',' >> double_), // double,double,double,double
            // End expression
            space
        );

        if(!r || first != last) {
            return false;
        }

        return r;
    }

}


#endif
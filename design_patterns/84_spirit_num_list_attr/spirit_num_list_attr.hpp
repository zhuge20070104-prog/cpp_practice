#ifndef _FREDRIC_SPIRIT_NUM_LIST_ATTR_HPP_
#define  _FREDRIC_SPIRIT_NUM_LIST_ATTR_HPP_
#include <string>
#include <iostream>
#include <memory>
#include <functional>
#include <vector>
#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>


#include "log.h"

namespace client {
    namespace qi = boost::spirit::qi;
    namespace ascii = boost::spirit::ascii;
    namespace phoenix = boost::phoenix;

    template <typename Iterator>
    bool parse_numbers(Iterator first, Iterator last, std::vector<double>& v) {
        using qi::double_;
        using qi::phrase_parse;
        using qi::_1;
        using ascii::space;
        using phoenix::push_back;

        bool r = phrase_parse(
            first,
            last,
            // Start expression
            double_ >> *(',' >> double_), // double,double,double,double
            // End expression
            space,
            v
        );

        if(!r || first != last) {
            return false;
        }

        return r;
    }

}


#endif
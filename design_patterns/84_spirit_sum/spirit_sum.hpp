#ifndef _FREDRIC_SPIRIT_SUM_HPP_
#define _FREDRIC_SPIRIT_SUM_HPP_
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
    bool adder(Iterator first, Iterator last, double& n) {
        using qi::double_;
        using qi::phrase_parse;
        using ascii::space;
        using boost::phoenix::ref;
        using boost::spirit::qi::_1;

        bool r = phrase_parse(
            first,
            last,
            // Start expression
           (
                double_[ref(n) = _1] >> *('+' >> double_[ref(n) += _1])  // 1+2+3+4
           ),
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
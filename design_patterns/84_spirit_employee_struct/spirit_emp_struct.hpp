#ifndef _FREDRIC_SPIRIT_EMP_STRUCT_HPP_
#define _FREDRIC_SPIRIT_EMP_STRUCT_HPP_
#include <string>
#include <iostream>
#include <memory>
#include <functional>
#include <vector>
#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <complex>

#include "log.h"

namespace client {
    namespace qi = boost::spirit::qi;
    namespace ascii = boost::spirit::ascii;

    struct Employee {
        int age;
        std::string sur_name;
        std::string fore_name;
        double salary;
    };
}

// 注册Employee到boost::fusion 命名空间
BOOST_FUSION_ADAPT_STRUCT(
    client::Employee,
    (int, age)
    (std::string, sur_name)
    (std::string, fore_name)
    (double, salary)
)

namespace  client {
    // Employee解析语法
    template <typename Iterator>
    struct EmployeeParser: qi::grammar<Iterator, Employee(), ascii::space_type> {
        EmployeeParser(): EmployeeParser::base_type(start) {
            using qi::int_;
            using qi::lit;
            using qi::double_;
            using qi::lexeme;
            using boost::spirit::qi::char_;

            // lexeme 不允许跳过空格
            quoted_string %= lexeme['"' >> +(char_ - '"') >> '"'];
            start %= lit("Employee") 
                >> '{'
                >> int_ >> ','
                >> quoted_string >> ','
                >> quoted_string >> ','
                >> double_
                >>'}';
        }

        qi::rule<Iterator, std::string(), ascii::space_type> quoted_string;
        qi::rule<Iterator, Employee(), ascii::space_type> start;
    };
} // namespace  client

#endif
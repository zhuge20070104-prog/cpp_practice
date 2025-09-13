#include <iostream>
#include <sstream>
#include <regex>
#include <vector>
#include <string>
#include <set>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

int const max_recur_depth_ {50};

bool should_ignore(const std::set<std::string>& ignore_list_in_lower, const std::string& name) {
    auto n = std::move(name);
    for (auto & c: n) c = tolower(c);
    for (auto & i : ignore_list_in_lower) {
        if (n.find(i) != std::string::npos)
            return true;
    }
    return false;
}

bool json_evaluate(const json& exp, const json& act, const std::set<std::string>& ignore_list_in_lower, int recur_depth, bool allow_missing)
{
    if (recur_depth > max_recur_depth_ || exp.type() != act.type()
    || (exp.size() > act.size() && (exp.is_array() || !allow_missing)))
        return false;
    if (!exp.is_array() && !exp.is_object())
        return exp == act;
    bool ret = true;

    if (exp.is_object())
        for (auto iter = exp.begin(); iter != exp.end(); ++iter)
        {
            if (should_ignore(ignore_list_in_lower, iter.key()))
                continue;
            if (act.find(iter.key()) == act.end())
            {
                if (allow_missing)
                    continue;
                else
                    return false;
            }
            if (!json_evaluate(*iter, act[iter.key()], ignore_list_in_lower, recur_depth + 1, allow_missing))
                return false;
        }
    else if (exp.is_array())
        for (int i = 0; i < exp.size(); ++i)
        {
            if (!json_evaluate(exp[i], act[i], ignore_list_in_lower, recur_depth + 1, allow_missing))
                return false;
        }

    return ret;
}


int main(int argc, char* argv[]) {
    
    auto exp = json::parse(R"([{
        "name": "ZhangSan",
        "age": 23
    }])");

    auto act = json::parse(R"([{
        "name": "ZhangSan",
        "age": 23
    }])");


    bool res = json_evaluate(exp, act, {}, 0, true);
    std::cout << std::boolalpha << res << std::endl;


    return EXIT_SUCCESS;
}
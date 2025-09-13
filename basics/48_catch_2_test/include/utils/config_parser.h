#ifndef _FREDRIC_CONFIG_PARSER_H_
#define _FREDRIC_CONFIG_PARSER_H_

#include <string>
#include <memory>
#include "json/json.hpp"
#include "funcs.h"

using ordered_json = nlohmann::ordered_json;

namespace tn {
namespace integration_test {

// TODO: add cfg_options fields
struct cfg_options_t {
    int params1;
    std::string params2;
};

struct config_parser_t {
    config_parser_t(std::string const& cfg_path_): cfg_path(cfg_path_) {}
    
    // TODO: add parse config options code
    std::shared_ptr<cfg_options_t> parse() {
        std::shared_ptr<cfg_options_t> options(new cfg_options_t());
        auto content = get_file_content(cfg_path);
        auto cfg_js = ordered_json::parse(content);
        options->params1 = cfg_js["params1"].get<int>();
        options->params2 = cfg_js["params2"].get<std::string>();
        return options;
    }

    std::string cfg_path;
};

}
}

#endif
#include "property_tree_json.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <exception>

namespace pt = boost::property_tree;
using ptree = boost::property_tree::ptree;
using ptree_value_type = ptree::value_type;

namespace client {
    debug_settings::debug_settings(std::string const& file_name):
        m_file_name(file_name) {}
    
    void debug_settings::load() {
        ptree tree;
        pt::read_json(m_file_name, tree);
        m_file = tree.get<std::string>("debug.file_name");
        m_level = tree.get("debug.level", 0);
        auto modules = tree.get_child("debug.modules");
        std::for_each(modules.begin(), modules.end(), [&](ptree_value_type const& v) {
            m_modules.push_back(v.second.data());
        });
    }

    void debug_settings::save() {
        ptree tree;
        tree.put("debug.file_name", m_file);
        tree.put("debug.level", m_level);

        ptree modules; 
        std::for_each(m_modules.begin(), m_modules.end(), [&modules](std::string const& module) {
            modules.push_back(ptree_value_type{"", module});
        });
        tree.add_child("debug.modules", modules);
        pt::write_json(m_file_name, tree);
    }
};
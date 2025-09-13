#ifndef _FREDRIC_PROPERTY_TREE_XML_H_
#define _FREDRIC_PROPERTY_TREE_XML_H_
#include <string>
#include <iostream>
#include <memory>
#include <functional>
#include <vector>
#include <boost/config/warning_disable.hpp>


#include "log.h"

namespace client {
  struct debug_settings {
    std::string m_file;
    int m_level;
    std::vector<std::string> m_modules;

    debug_settings(std::string const& file_name);
    void load();
    void save();
private:
    std::string m_file_name;
  };
}


#endif
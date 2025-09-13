#include "log.h"


void init_log(){
    logging::register_simple_formatter_factory<
    boost::log::trivial::severity_level, char>("Severity");

    logging::add_file_log(
        keywords::target = "logs/", keywords::file_name = "%y%m%d_%3N.log",
        keywords::rotation_size = 10 * 1024 * 1024,
        keywords::scan_method = sinks::file::scan_matching,
         keywords::format =
            (
                expr::stream
                << "[" << logging::trivial::severity
                << "]" << expr::smessage
            )
        );

    logging::add_console_log(std::cout,
                             boost::log::keywords::format = ">> %Message%");

    logging::core::get()->set_filter(logging::trivial::severity >=
                                     logging::trivial::info);
}
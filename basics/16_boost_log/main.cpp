#include <boost/log/common.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/keywords/name.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/attributes/mutable_constant.hpp>

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace keywords = boost::log::keywords;
namespace attrs = boost::log::attributes;
namespace expr = boost::log::expressions;

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

#define B_LOG(level) BOOST_LOG_TRIVIAL(level) << "["<< __FILE__ << ":" << __LINE__ << ":" << __func__ <<  "]"

int main(int argc, char* argv[]) {
    init_log();
    B_LOG(info) << "Hello world" << std::endl;    
    
    return EXIT_SUCCESS;
}
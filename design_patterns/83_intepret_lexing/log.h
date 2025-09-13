#ifndef _FREDRIC_LOG_H_
#define _FREDRIC_LOG_H_

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

void init_log();

#define B_LOG(level) BOOST_LOG_TRIVIAL(level) << "["<< __FILE__ << ":" << __LINE__ << ":" << __func__ <<  "]"

#endif
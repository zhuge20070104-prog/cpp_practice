#include "Poco/LocalDateTime.h"
#include "Poco/DateTime.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/DateTimeParser.h"

#include <iostream>

using Poco::LocalDateTime;
using Poco::DateTime;
using Poco::DateTimeFormat;
using Poco::DateTimeFormatter;
using Poco::DateTimeParser;

namespace DT {

    const static Poco::Timespan::TimeDiff TZ_DIFF = Poco::Timespan::HOURS * 8;
    struct DateTime {
        static std::string get_current_datetime_str() {
            LocalDateTime now;
            now += TZ_DIFF;
            std::string str = DateTimeFormatter::format(now, "%Y-%m-%d %H:%M:%S");
            return str;
        }

        static std::string format_date_time(LocalDateTime const& ldt) {
            std::string str = DateTimeFormatter::format(ldt, DateTimeFormat::SORTABLE_FORMAT);
            return str;
        }

        static LocalDateTime get_current_datetime() {
            LocalDateTime now;
            now += TZ_DIFF;
            return now;
        }

        /**
         * tzd is in seconds
         * */
        static LocalDateTime parse_date_time(std::string const& time_str, int tzd=0) {
            int tzd_zero = 0;
            Poco::DateTime dt;
            DateTimeParser::parse("%Y-%m-%d %H:%M:%S", time_str, dt, tzd_zero);
            LocalDateTime ldt(tzd, dt); 
            return ldt;
        }
    };
}



int main(int argc, char* argv[]) {
    std::cout << DT::DateTime::get_current_datetime_str() << std::endl;
    auto datetime = DT::DateTime::parse_date_time("2022-12-05 17:31:25");
    std::cout << DT::DateTime::format_date_time(datetime) << std::endl;

    auto now = DT::DateTime::get_current_datetime();
    auto now_str = DT::DateTime::format_date_time(now);
    std::cout << now_str << std::endl;
    return EXIT_SUCCESS;
}
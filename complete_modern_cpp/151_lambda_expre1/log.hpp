#ifndef _FREDRIC_LOG_HPP_
#define _FREDRIC_LOG_HPP_

template <typename STREAM,  typename T> 
void log_content(STREAM& stream, T const& t) {
    stream << t << std::endl;
    stream << std::endl;
}

template <typename STREAM, typename T, typename ... Args>
void log_content(STREAM& stream, T const& t, Args ... args) {
        stream << t <<" ";
        log_content(stream, args...);
}

#define LOG(stream,  ...)   \
    stream << __FILE__ << ":" << __LINE__ << std::endl; \
    log_content(stream, __VA_ARGS__); \

#endif
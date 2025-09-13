#include <iostream>
#include <regex>


#include <iostream>  
#include <fstream>  
#include <vector>  
#include <string>  
  
#include <iostream>  
#include <fstream>  
#include <vector>  
#include <string> 
#include <iomanip>
#include <chrono>
#include <ctime>

int const log_seconds_diff = 30;

std::chrono::system_clock::time_point convert_string_to_time_point(std::string const& s) {
    std::istringstream ss(s);
    std::tm tm = {};
    ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
    if (ss.fail()) {
        // 处理转换失败的情况
        throw std::runtime_error("Failed to convert the string to a time_point.");
    }
    
    return std::chrono::system_clock::from_time_t(std::mktime(&tm));
}

std::string pad_zero(int num) {
    std::stringstream result_ss;
    if(num < 10) {
        result_ss << 0 << num;
    } else {
        result_ss << num;
    }
    return result_ss.str();
}

std::string convert_time_point_to_string(std::chrono::system_clock::time_point const& tp) {
     
    // 转换为time_t  
    std::time_t now_c = std::chrono::system_clock::to_time_t(tp);  
    std::tm* now_tm = std::localtime(&now_c);
    std::stringstream time_ss;
    time_ss <<  now_tm->tm_year + 1900 << "-" << pad_zero(now_tm->tm_mon + 1)
        << "-" << pad_zero(now_tm->tm_mday) << " " << pad_zero(now_tm->tm_hour) << ":"
        << pad_zero(now_tm->tm_min) << ":" << pad_zero(now_tm->tm_sec);

    return time_ss.str();
}

struct log_match {
    bool result;
    std::string date_time;
    std::string line;
};

std::vector<std::string> read_last_n_lines(const std::string& filename, size_t n) {
    if(n == 0) {
        return {};
    } 

    std::ifstream file(filename, std::ios::binary | std::ios::ate);  
    
    if(!file) {  
        std::cerr << "Could not open file: " << filename << std::endl;  
        return {};  
    }  
      
    std::streamsize size = file.tellg();  
    if (size == 0) {  
        // Empty file  
        return {};  
    }  
            
    // Read from the end of the file towards the beginning  
    size_t bytes_to_read = std::min<std::size_t>(size, 128); // Start with a reasonable buffer size  
    std::streampos file_size = file.tellg(); 
    int start_pos = file_size;
    std::string lines_buffer;
    std::string cur_buffer;

    while(start_pos > 0 && std::count(lines_buffer.begin(), lines_buffer.end(), '\n') < n+1) {
        start_pos = start_pos - bytes_to_read;
        int cur_read = bytes_to_read;
        if(start_pos < 0) {
            start_pos = 0;
            cur_read = start_pos + bytes_to_read;
        } 
        file.seekg(start_pos);
        cur_buffer.clear();
        cur_buffer.resize(cur_read);
        file.read(cur_buffer.data(), cur_buffer.size());
        lines_buffer = cur_buffer + lines_buffer;
    }
    
    // Remove it, just for debugging purpose
    // std::cout << "current buffer: " << std::endl;
    // std::cout << lines_buffer << std::endl;
    // std::cout << "===================end buffer===================" << std::endl;
    
    file.close();

    std::vector<std::string> lines;  
    std::string line;  
    size_t pos = 0;  
      
    // Process the buffer to extract lines  
    while (pos < lines_buffer.size() && lines.size() < n + 1) {  
        size_t newline_pos = lines_buffer.find('\n', pos);  
        if (newline_pos == std::string::npos) {  
            // No more newlines, append the rest of the buffer as one line  
            line += std::string(lines_buffer.begin() + pos, lines_buffer.end());  
            lines.push_back(line);  
            break;  
        } else {
            // Append the current line to the vector  
            line += std::string(lines_buffer.begin() + pos, lines_buffer.begin() + newline_pos);  
            lines.push_back(line);  
            line.clear(); // Reset line for the next iteration  
            pos = newline_pos + 1; // Move to the next character after the newline  
        }  
    } 

    if(lines.size() > 1) {
        lines = std::vector<std::string>(lines.begin() + 1, lines.end());
    }

    return lines;  
}  


struct logger_getter_t {
    logger_getter_t(std::string const& log_file_path_): log_file_path(log_file_path_) {}

    log_match match_text(std::string const& matched_text) {
        auto lines = read_last_n_lines(log_file_path, 50);
        std::stringstream matched_pattern_ss;
        //2024-04-17 08:48:21
        matched_pattern_ss << ".*(\\d{4}-\\d{2}-\\d{2} \\d{2}:\\d{2}:\\d{2}).*(" << matched_text  <<").*";
        std::cout << matched_pattern_ss.str() << std::endl;
        std::regex matched_pattern(matched_pattern_ss.str());
        for(auto const& line: lines) {
            std::smatch result;
            if(std::regex_match(line, result, matched_pattern)) {
                std::string log_date = result.str(1).data();

                auto now_point = std::chrono::system_clock::now();
                auto log_point = convert_string_to_time_point(log_date);   
                auto seconds_diff = std::chrono::duration_cast<std::chrono::seconds>(now_point - log_point).count();
                if(seconds_diff < log_seconds_diff) {
                    return log_match{true, log_date, line};
                }
            }
        }
        std::string cur_time = convert_time_point_to_string(std::chrono::system_clock::now());
        return log_match {false, cur_time, matched_text};
    }

private:
    std::string log_file_path;    
};

int main(int argc, char* argv[]) {
    std::string file_name = "../planning.log";
    logger_getter_t log_getter(file_name);
    auto log_match_res = log_getter.match_text("kPlanSearching --> kPlanFailed");
    std::cout << std::boolalpha << log_match_res.result 
        << ", " << log_match_res.date_time << 
        std::endl 
        << log_match_res.line << std::endl;
    return EXIT_SUCCESS;
}
#include <iostream>
#include <regex>

std::string match_ps_desc(std::string const& entire_str) {
    std::regex pattern(R"(^[\s\S]+CheryCV_X50_blue_([\s\S]+)_Angle[\s\S]+$)");
    std::regex no_suffix_pattern(R"(^[\s\S]+CheryCV_X50_blue_([\s\S]+)$)");
    std::smatch result;
    
    std::regex ultrasound_pattern(R"(.*[\S]+[\s](.*)[\s][\S]+)");
        
    if (std::regex_search(entire_str, result, pattern)) {
        std::cout << "Matched!" << std::endl;
        return result.str(1).data();
    } else if(std::regex_match(entire_str, result, no_suffix_pattern)) {
        std::cout << "No suffix pattern Matched!" << std::endl;
        return result.str(1).data();
    } else if(std::regex_match(entire_str, result, ultrasound_pattern)) {
        std::cout << "Ultra Matched!" << std::endl;
        return result.str(1).data();
    }
    std::cout << "Not matched" << std::endl;

    return "Unknown";
}


int main(int argc, char* argv[]) {
    // std::string src_desc = "2023-02-03-00-00-01_StitchedImage_大阳垾湿地公园_CheryCV_X50_blue_地面-地砖车位_Angle_1";
    // std::string src_desc = "2023-01-12-11-00-02_SurroundViewCameraFrames_芜湖市盟博园区_CheryCV_X50_blue_地下-车位_Angle_0";
    // std::string src_desc = "BAIC 20240110 空间垂直_外八_2点8米 2024-01-10-10-52-14_6";
    // std::string src_desc = "BAIC 20240110 空间垂直_内八_2点8米 2024-01-10-11-15-37_7";
    std::string src_desc =  "2023-01-12-11-00-02_SurroundViewCameraFrames_芜湖市盟博园区_CheryCV_X50_blue_地下-车位";

    auto res = match_ps_desc(src_desc);
    std::cout << "Matched Res: " << res << std::endl;
    return EXIT_SUCCESS;
}
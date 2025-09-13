#include <regex>
#include <iostream>


int main(int argc, char* argv[]) {
    // std::string desc_s = "Case: 2.2023-02-03-00-00-01_StitchedImage_大阳垾湿地公园_CheryCV_X50_blue_地面-地砖车位_Angle_1";
    std::string desc_s = "Case: 100.2022-12-09-00-00-02_StitchedImage_金虹桥国际中心_CheryCV_X50_blue_地下-平行车位_Angle_9";
    std::regex pattern(R"(.*Case:\s+(\d+)\.(.*)$)");
    std::smatch result;

    if (std::regex_search(desc_s, result, pattern)) {
        std::cout << result.str(1) << std::endl;
        std::cout << result.str(2) << std::endl;
    }
  
    return EXIT_SUCCESS;
}
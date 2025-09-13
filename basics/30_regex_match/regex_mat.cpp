#include <iostream>
# include <string>
#include <regex>
#include <sstream>

void match_location_rectified() {
    std::string msg_str = "INFO|2023-06-16 14:26:32.839123159|3914.843|2252|2506|strategy|strategy|planning/src/log_utils.cpp|214|PlanningNode::Plan car_pose_:(57.144993,-12.358267,-0.289201)";
    std::regex pattern(R"(.*car_pose_:\((.*),(.*),(.*)\)$)");
    std::smatch result;

    if (std::regex_search(msg_str, result, pattern)) {
        std::cout << result.str(1) << std::endl;
        std::cout << result.str(2) << std::endl;
        std::cout << result.str(3) << std::endl;
    }
}

void match_plan_cmd_type() {
    std::string msg_str = "14:24:49.593935459|3811.598|2252|2506|strategy|strategy|planning/src/log_utils.cpp|214|PlanningNode::OnPlanCmd plan_type:kTailInParkingOutToRight";
    std::regex pattern(R"(.*plan_type:(.*)$)");
    std::smatch result;

    if (std::regex_search(msg_str, result, pattern)) {
        std::cout << result.str(1) << std::endl;
    }
}

enum class AssignType {
    AssignWithDepth,
    AssignWithOutDepth
};
void match_plan_cmd_parking_space() {
    //INFO|2022-07-28 15:12:38.735353765|843.896|3312|3525|strategy|planning/src/log_utils.cpp|214|PlanningNode::OnPlanCmd parking_space:id:-1 type:1 sensor:0 is_target:111 is_mechanical:0 is_handicap:0 valid:1 avaiable_type:2 (2.458424,3.541270),(4.836646,8.389365),(2.771716,9.402310),(0.393495,4.554216)
	// std::string msg_str = "INFO|2023-06-16 11:21:46.818262958|4126.158|3355|3474|strategy|strategy|planning/src/log_utils.cpp|214|PlanningNode::OnPlanCmd parking_space:id:-1 type:2 sensor:1 is_target:32 is_mechanical:0 is_handicap:0 valid:1 depth:2.050000 ob_left:0 ob_right:0 avaiable_type:2 (-11.242037,8.677540),(-11.403429,10.721177),(-17.384806,10.248809),(-17.223413,8.205172)";
    std::string msg_str  = "INFO|2022-07-28 15:12:38.735353765|843.896|3312|3525|strategy|planning/src/log_utils.cpp|214|PlanningNode::OnPlanCmd parking_space:id:-1 type:1 sensor:0 is_target:111 is_mechanical:0 is_handicap:0 valid:1 avaiable_type:2 (2.458424,3.541270),(4.836646,8.389365),(2.771716,9.402310),(0.393495,4.554216)";
    std::string regex_ = R"(.*sensor:(\d+).*is_mechanical:(\d+).*is_handicap:(\d+).*valid:(\d+).*depth:(\d+\.\d+).*ob_left:(\d+).*ob_right:(\d+).*avaiable_type:(\d+).*\((.*),(.*)\),\((.*),(.*)\),\((.*),(.*)\),\((.*),(.*)\)$)";
   AssignType assign = AssignType::AssignWithDepth;
    if(msg_str.find("ob_left") == std::string::npos) {
        assign = AssignType::AssignWithOutDepth;
        regex_ = R"(.*sensor:(\d+).*is_mechanical:(\d+).*is_handicap:(\d+).*valid:(\d+).*avaiable_type:(\d+).*\((.*),(.*)\),\((.*),(.*)\),\((.*),(.*)\),\((.*),(.*)\)$)";
    }
    std::regex pattern(regex_);
    std::smatch result;

    if (std::regex_search(msg_str, result, pattern))
    {
        std::cout << "sensor: " << result.str(1) << " is_mechanical: " << result.str(2) << std::endl;
        std::cout << "is_handicap: " << result.str(3) << std::endl;
		std::cout << "is_valid: " << result.str(4) 
        
        << " depth:" << result.str(5) << std::endl;
        std::cout << "ob_left: " << result.str(6) << std::endl;
		std::cout << "ob_right: " << result.str(7) 
        
        << " avaiable_type:" << result.str(8) << std::endl;
        
        std::cout << "space: " << result.str(9) << std::endl;
        std::cout << "space: " << result.str(10) << std::endl;
		std::cout << "space: " << result.str(11) << std::endl;
		std::cout << "space: " << result.str(12) << std::endl;
        std::cout << "space: " << result.str(13) << std::endl;
        std::cout << "space: " << result.str(14) << std::endl;
		std::cout << "space: " << result.str(15) << std::endl;
		std::cout << "space: " << result.str(16) << std::endl;
    }

}



void match_parking_space_fusioned() {
    // INFO|2023-03-27 14:40:49.620719170|525.624|3142|4079|strategy|strategy|planning/src/log_utils.cpp|214|TraslateToLocal ps:id:6 type:1 sensor:0 is_target:0 is_mechanical:0 is_handicap:0 valid:0 depth:4.717632 ob_left:0 ob_right:0 avaiable_type:0 (35.918514,0.506924),(41.180553,-0.705868),(41.697105,1.535368),(36.435078,2.748160) ob types (0, )
    // INFO|2023-06-16 11:22:47.402656053|4186.743|3355|4243|strategy|strategy|planning/src/log_utils.cpp|214|TraslateToLocal ps:id:-1 type:2 sensor:1 is_target:1 is_mechanical:0 is_handicap:0 valid:1 depth:2.050000 ob_left:0 ob_right:0 avaiable_type:2 (-11.112824,8.311578),(-11.301772,10.704128),(-17.482529,10.216014),(-17.293581,7.823463)
    // std::string msg_str = "INFO|2023-03-27 14:40:49.620719170|525.624|3142|4079|strategy|strategy|planning/src/log_utils.cpp|214|TraslateToLocal ps:id:6 type:1 sensor:0 is_target:0 is_mechanical:0 is_handicap:0 valid:0 depth:4.717632 ob_left:0 ob_right:0 avaiable_type:0 (35.918514,0.506924),(41.180553,-0.705868),(41.697105,1.535368),(36.435078,2.748160) ob types (0, )";
    std::string msg_str = "INFO|2022-07-28 15:12:38.749418920|843.910|3312|4272|strategy|planning/src/log_utils.cpp|214|TraslateToLocal ps:id:1 type:1 sensor:0 is_target:0 is_mechanical:0 is_handicap:0 valid:1 avaiable_type:2 (2.458390,3.541595),(4.839066,8.388484),(2.774650,9.402474),(0.393974,4.555587)";
    auto pos = msg_str.find("ob types");
    if(pos != std::string::npos) {
        msg_str = msg_str.substr(0, pos);
    }

    std::string regex_ = R"(.*sensor:(\d+).*is_mechanical:(\d+).*is_handicap:(\d+).*valid:(\d+).*depth:(\d+\.\d+).*ob_left:(\d+).*ob_right:(\d+).*avaiable_type:(\d+).*\((.*),(.*)\),\((.*),(.*)\),\((.*),(.*)\),\((.*),(.*)\).*)";
    AssignType assign = AssignType::AssignWithDepth;
    if(msg_str.find("ob_left") == std::string::npos) {
        assign = AssignType::AssignWithOutDepth;
        regex_ = R"(.*sensor:(\d+).*is_mechanical:(\d+).*is_handicap:(\d+).*valid:(\d+).*avaiable_type:(\d+).*\((.*),(.*)\),\((.*),(.*)\),\((.*),(.*)\),\((.*),(.*)\).*)";
    }
    std::regex pattern(regex_);
    std::smatch result;

    std::cout << "msg_str: " << msg_str << "\n";
    if (std::regex_search(msg_str, result, pattern))
    {
        std::cout << "sensor: " << result.str(1) << " is_mechanical: " << result.str(2) << std::endl;
        std::cout << "is_handicap: " << result.str(3) << std::endl;
		std::cout << "is_valid: " << result.str(4) << " depth:" << result.str(5) << std::endl;
        std::cout << "ob_left: " << result.str(6) << std::endl;
		std::cout << "ob_right: " << result.str(7) << " avaiable_type:" << result.str(8) << std::endl;
        std::cout << "space: " << result.str(9) << std::endl;
        std::cout << "space: " << result.str(10) << std::endl;
		std::cout << "space: " << result.str(11) << std::endl;
		std::cout << "space: " << result.str(12) << std::endl;
        std::cout << "space: " << result.str(13) << std::endl;
        std::cout << "space: " << result.str(14) << std::endl;
		std::cout << "space: " << result.str(15) << std::endl;
		std::cout << "space: " << result.str(16) << std::endl;
    }
}



void match_uss_points() {
    // INFO|2023-06-16 11:33:55.917206183|4855.257|3355|4404|strategy|strategy|planning/src/log_utils.cpp|214|PlannerController::FillUssPoints uss_data_near:(94.9555,-30.1439),(94.8628,-30.0782),(94.9755,-30.098),(94.8837,-30.0327),(94.9097,-30.0028),(95.3546,-30.0351),(95.4297,-30.0413),(94.8892,-29.9783),(94.932,-29.9581),(94.9475,-29.9143),(94.9511,-29.9323),(94.9328,-29.8883),(94.9996,-29.8851),(95.0307,-29.8884),(95.0768,-29.8934),(94.9967,-29.8433),(95.023,-29.8409),(95.0961,-29.8381),(95.101,-29.8497),(94.9764,-29.7983),(95.0464,-29.7967),(95.0856,-29.7868),(95.1496,-29.7623),(95.1583,-29.7533),(95.0435,-29.7343),(95.0931,-29.7083),(95.1495,-29.7183),(95.1739,-29.7186),(95.0201,-29.6636),(95.0878,-29.6653),(95.1479,-29.6676),(95.1981,-29.6749),(95.2068,-29.6659),(94.9775,-29.6328),(95.018,-29.6476),(95.1398,-29.6199),(95.1976,-29.6306),(95.2224,-29.6311),(95.29,-29.6085),(95.3354,-29.6247),(95.034,-29.5703),(95.0709,-29.5976),(95.1266,-29.5537),(95.1939,-29.5625),(95.2467,-29.5874),(95.2554,-29.5785),(100.08,-29.5938),(95.0926,-29.5278),(95.1446,-29.5328),(95.1682,-29.5318),(100.034,-29.5051),(100.086,-29.5078),(100.142,-29.5339),(100.183,-29.518),(100.011,-29.4607),(100.096,-29.4749),(100.143,-29.4668),(100.161,-29.473),(99.9879,-29.4163),(100.038,-29.4198),(100.097,-29.4444),(100.139,-29.428),(100.526,-29.4035),(100.558,-29.4273),(99.9648,-29.372),(100.033,-29.3554),(100.098,-29.3772),(100.117,-29.383),(100.486,-29.3738),(100.502,-29.3857),(99.8229,-29.3204),(99.8718,-29.3044),(99.9418,-29.3276),(100.096,-29.338),(100.397,-29.3083),(100.445,-29.344),(100.453,-29.35),(99.8853,-29.2524),(99.9187,-29.2832),(100.219,-29.2541),(100.325,-29.2548),(100.365,-29.2845),(99.8278,-29.2371),(99.8707,-29.2432),(99.9341,-29.2411),(100.205,-29.2398),(100.285,-29.2251),(100.301,-29.237),(100.244,-29.1953),(100.293,-29.1542),(100.301,-29.1825),(100.276,-29.1451),(100.321,-29.1435),(100.284,-28.7505),(100.291,-28.7402),(100.341,-28.7372),(100.391,-28.7341),(100.441,-28.7311),(100.491,-28.728),(100.541,-28.725),(100.59,-28.7219),(100.64,-28.7189),(100.562,-28.6967),(100.606,-28.6988),
    // INFO|2023-06-16 11:33:55.917419143|4855.257|3355|4404|strategy|strategy|planning/src/log_utils.cpp|214|PlannerController::FillUssPoints uss_data_far:(95.6786,-30.3474),(95.7309,-30.3488),(97.1178,-30.112),(94.986,-30.061),(95.0367,-30.0749),(95.0882,-30.0853),(95.1065,-30.055),(95.1765,-30.0589),(95.2182,-30.0599),(95.253,-30.0547),(94.8409,-30),(94.8879,-30.0235),(94.9363,-30.0439),(94.9949,-30.0324),(95.0437,-30.0457),(95.0949,-30.0459),(94.7955,-29.9735),(94.8008,-29.965),(94.8551,-29.9737),(94.9004,-29.9963),(94.7105,-29.9118),(94.752,-29.944),(94.8115,-29.9481),(94.7296,-29.8887),(94.759,-29.8909),(95.085,-29.8558),(94.9439,-29.8051),(94.9894,-29.8258),(95.0366,-29.8428),(94.8586,-29.7527),(94.9001,-29.7806),(94.8194,-29.7215),(99.9055,-29.6164),(99.9535,-29.6031),(100.001,-29.5872),(100.092,-29.5477),(100.136,-29.5243),(100.179,-29.4985),(100.22,-29.4704),(99.8724,-29.4494),(99.9191,-29.4357),(99.9647,-29.4189),(100.297,-29.4076),(100.009,-29.3991),(100.052,-29.3765),(100.333,-29.3731),(100.133,-29.323),(100.171,-29.2924),(100.207,-29.2593),
    std::string msg_str = "INFO|2023-06-16 11:25:03.552423768|4322.892|3355|4283|strategy|strategy|planning/src/log_utils.cpp|214|PlannerController::FillUssPoints uss_data_far:";
    std::regex pattern(R"(.*FillUssPoints.*:(\((.*),(.*)\),)+$)");
    std::smatch result;

    if (std::regex_search(msg_str, result, pattern)) {
        std::cout << " " << result.str(1) << std::endl;
        auto tmp_ = std::regex_replace(result.str(1), std::regex(R"(\()"), "");
        tmp_ = std::regex_replace(tmp_, std::regex(R"(\))"), "");
        std::stringstream iss(tmp_);
        std::string ele;
        int i = 0;
        while(std::getline(iss, ele, ',')) {
            
            if(i%2 == 0) {
                std::cout << "x: " << ele << " ";
            } else {
                std::cout << "y: " << ele;
                 std::cout << std::endl;
            }
            i++;
        }
    }else {
        std::cout << "Not matched" << std::endl;
    }
}

void match_detection_obj_fusioned() {
    // INFO|2023-10-27 14:10:51.392982411|19924.678|20345|20465|planning|planning|planning/src/log_utils.cpp|259|PlannerController::OccupancyROI detected_object_list:(0.967742,2.525),(0.967742,2.875),(0.617742,2.875),(0.617742,2.525),kPillar
    std::string msg_str = "INFO|2023-10-27 14:10:51.392982411|19924.678|20345|20465|planning|planning|planning/src/log_utils.cpp|259|PlannerController::OccupancyROI detected_object_list:(0.967742,2.525),(0.967742,2.875),(0.617742,2.875),(0.617742,2.525),kPillar";
    std::regex pattern(R"(.*:\((.*),(.*)\),\((.*),(.*)\),\((.*),(.*)\),\((.*),(.*)\),(.*)$)");
    std::smatch result;

    if (std::regex_search(msg_str, result, pattern)) {
        std::cout << result.str(1) << ", " << result.str(2) << "\n";
        std::cout << result.str(3) << ", " << result.str(4) << "\n";
        std::cout << result.str(5) << ", " << result.str(6) << "\n";
        std::cout << result.str(7) << ", " << result.str(8) << "\n";
        std::cout << result.str(9) << "\n";
    }
}

int main(int argc, char* argv[]) {
    match_plan_cmd_parking_space();
    // match_plan_cmd_type();
	// match_location_rectified();
    // match_parking_space_fusioned();
    // match_uss_points();
    // match_detection_obj_fusioned();
    return EXIT_SUCCESS;
}
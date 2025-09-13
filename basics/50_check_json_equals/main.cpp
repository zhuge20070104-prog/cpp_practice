#include <nlohmann/json.hpp>  
#include <vector>  
#include <string>  
#include <iostream>

using ordered_json = nlohmann::ordered_json;

// 递归检查两个JSON值是否相等（基础实现）  
bool checkJsonEqual(ordered_json const& lhs, ordered_json const& rhs) {  
    
    // 检查两个JSON值是否都是相同的类型  
    if (lhs.type() != rhs.type()) {  
        return false;  
    }  
  
    // 递归地处理各种类型  
    switch (lhs.type()) {  
        case nlohmann::json::value_t::null:  
            // 空值总是相等的  
            return true;  
        case nlohmann::json::value_t::boolean:  
            // 布尔值比较  
            return lhs.get<bool>() == rhs.get<bool>();  
        case nlohmann::json::value_t::number_integer:  
            // 整数比较  
            return lhs.get<int64_t>() == rhs.get<int64_t>();  
        case nlohmann::json::value_t::number_unsigned:  
            // 无符号整数比较  
            return lhs.get<uint64_t>() == rhs.get<uint64_t>();  
        case nlohmann::json::value_t::number_float:  
            // 浮点数比较（注意：由于浮点数的精度问题，可能需要设置容差）  
            return (lhs.get<double>() - rhs.get<double>()) < 0.0001;  
        case nlohmann::json::value_t::string:  
            // 字符串比较  
            return lhs.get<std::string>() == rhs.get<std::string>();  
        case nlohmann::json::value_t::array: {  
            // 数组比较：递归检查数组中的每个元素  
            if (lhs.size() != rhs.size()) {  
                return false;  
            }  
            for (size_t i = 0; i < lhs.size(); ++i) {  
                if (!checkJsonEqual(lhs[i], rhs[i])) {  
                    return false;  
                }  
            }  
            return true;  
        }  
        case nlohmann::json::value_t::object: {  
            // 对象比较：递归检查对象的每个键值对  
            if (lhs.size() != rhs.size()) {  
                return false;  
            }  
            for (const auto& kvp : lhs.items()) {  
                // 检查rhs中是否有相同的键  
                auto rhs_it = rhs.find(kvp.key());  
                if (rhs_it == rhs.end() || !checkJsonEqual(kvp.value(), *rhs_it)) {  
                    return false;  
                }  
            }  
            return true;  
        }  
        case nlohmann::json::value_t::discarded:  
            // 被丢弃的值不能比较  
            return false;  
        default:  
            // 不支持的类型，或库内部使用的类型  
            return false;  
    }   
} 

// 递归检查两个JSON对象在指定字段上是否相等  
bool checkJsonFieldsEqual(ordered_json const& lhs, ordered_json const& rhs, const std::vector<std::string>& fields, 
    std::vector<std::string>& not_equal_fields) {  
    // 遍历所有字段  
    for (const auto& field : fields) {  
        // 检查字段是否存在  
        if (!lhs.contains(field) || !rhs.contains(field)) { 
            not_equal_fields.push_back(field); 
            return false; // 如果任一对象缺少字段，则不相等  
        }  
  
        // 递归检查字段值是否相等  
        if (!checkJsonEqual(lhs[field], rhs[field])) {
            not_equal_fields.push_back(field);  
            return false; // 如果字段值不相等，则整个对象不相等  
        }  
    }  
  
    // 所有指定字段都相等  
    return true;  
}  
  

  
int main() {  
    // 创建两个JSON对象  
    ordered_json json1 = {  
        {"name", "John"},  
        {"age", 30},  
        {"cars", {{"Brand1", 1.2301}, {"Brand2", "BMW"}, {"Brand3", "Fiat"}}}  
    };  
  
    ordered_json json2 = {  
        {"name", "John"},  
        {"age", 35}, // 注意这里的年龄被修改为35，以测试不等的情况  
        {"cars", {{"Brand1", 1.230000}, {"Brand2", "BMW"}, {"Brand3", "Fiat"}}}  
    };  

  
    // 指定需要比较的字段  
    std::vector<std::string> fieldsToCompare = {"name", "cars", "age"};  
  
    // 检查两个JSON对象在指定字段上是否相等  
    std::vector<std::string> not_equal_fields = {};
    bool areFieldsEqual = checkJsonFieldsEqual(json1, json2, fieldsToCompare, not_equal_fields);  
    if (areFieldsEqual) {  
        std::cout << "The specified fields of the two JSON objects are equal." << std::endl;  
    } else {  
        std::cout << "The specified fields of the two JSON objects are not equal." << std::endl;  
        std::cout << "The fields: [";
        for(auto const& not_equal_f: not_equal_fields) {
            std::cout << not_equal_f <<",";
        }
        std::cout << "] are not equal!\n";
    }  
  
    return 0;  
}
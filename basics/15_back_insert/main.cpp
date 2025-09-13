#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

struct Employee {
    std::string name;
    int age;
};

int main(int argc, char* argv[]) {
   std::vector<std::vector<Employee>>  sub_cases {{{"张三", 21}, {"李四", 22}}, {{"王五", 23}}, {{"钱七", 28}}};

   std::vector<Employee> result;
   for(auto const sub_case: sub_cases) {
      std::copy(sub_case.begin(), sub_case.end(), std::back_inserter(result));
   }

   sub_cases.clear();

   for(auto const& ele: result) {
        std::cout << ele.name  << " " << ele.age << " ";
   }
   std::cout << std::endl;
}
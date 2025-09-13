#include <iostream>
#include <string>
#include <typeinfo>
#include <cstdio>
#include <sstream>
#include <fstream>
#include <set>
#include <memory>
#include "boost/filesystem.hpp"
#include "gtest/gtest.h"
#include "log.hpp"
#include "assert_eq.h"
#include <functional>
#include <algorithm>
#include "contact.h"

void init_contacts() {
	ContactManager::add_contacts({
		Contact{"Fei", "Zhang", "11111", "22222", "zhangfei@telenav.cn", "当阳桥", "刘备帮", Group::Coworker},
		Contact{"Yu", "Guan", "33333", "44444", "guanyu@telenav.cn", "西柏坡", "刘备帮", Group::Coworker},
		Contact{"Su", "Lu", "22333", "22211", "lusu@telenav.cn", "江东", "孙权帮", Group::Acquaintance}
	});
}


// 根据FirstName进行排序
GTEST_TEST(TplTests, DisplayContactSortedByFirstName) {
	init_contacts();
	ContactManager::sort_by_name(SortMethod::FirstName);
}

// 根据LastName进行排序
GTEST_TEST(TplTests, DisplayContactSortedByLastName) {
	ContactManager::sort_by_name(SortMethod::LastName);
}

// 显示FirstName 和 primary number
GTEST_TEST(TplTests, DisplayFirstNameWithPrimaryNumber) {
	ContactManager::print_primary_number();
}

// 通过公司名过滤
GTEST_TEST(TplTests, FilterByCompany) {
	ContactManager::filter_and_print(FilterType::Company, "刘备帮");
}

// 根据Group分组打印
GTEST_TEST(TplTests, GroupedByGroup) {
	ContactManager::filter_and_print(FilterType::Grouped, "");
}

// 根据FirstName查询
GTEST_TEST(TplTests, FilterByFirstName) {
	ContactManager::filter_and_print(FilterType::FirstName, "Su");
}

// 根据LastName查询
GTEST_TEST(TplTests, FilterByLastName) {
	ContactManager::filter_and_print(FilterType::LastName, "Guan");
}

// Display count of Contacts by Company
GTEST_TEST(TplTests, DiplayCountByCompany) {
	ContactManager::group_count(CountType::Company);
}

// 分组显示count，根据Group字段
GTEST_TEST(TplTests, DisplayCountByGroup) {
	ContactManager::group_count(CountType::Group);
}
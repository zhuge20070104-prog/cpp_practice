#include "json.hpp"
#include <iostream>
# include <string>
#include <sstream>


using ordered_json = nlohmann::ordered_json;

struct person {
	std::string name;
	std::string sex;
	int age;
};

struct staff {
	std::string name;
	int salary;
};

struct message_serializer {

	message_serializer(): js_content() {}
	message_serializer(ordered_json& js_content_): js_content(js_content_) {}

	friend message_serializer& operator << (message_serializer& ser, std::string const& s) {
		ser.msg_ss << s;
		return ser;
	}

	friend message_serializer& operator >> (message_serializer& ser, person& p) {
		auto name = ser.js_content["name"].get<std::string>();
		auto sex = ser.js_content["sex"].get<std::string>();
		int age = ser.js_content["age"].get<int>();

		p.name = name;
		p.sex = sex;
		p.age = age;
		return ser;
	}

	friend message_serializer& operator << (message_serializer& ser, person  const& p) {
		ser.msg_ss << p.name << ", " << p.sex << ", " << p.age;
		return ser;
	}

	friend message_serializer& operator >> (message_serializer& ser, staff& p) {
		auto name = ser.js_content["name"].get<std::string>();
		int salary = ser.js_content["salary"].get<int>();

		p.name = name;
		p.salary = salary;
		return ser;
	}

	friend message_serializer& operator << (message_serializer& ser, staff  const& p) {
		ser.msg_ss << p.name << ", " << p.salary;
		return ser;
	}


	ordered_json json() {
		return js_content;
	}

	void json(ordered_json& js_content_) {
		js_content = js_content_;
	}

	void str(std::string const& str_) {
		msg_ss.str(str_);
	}

	std::string str() {
		return msg_ss.str();
	}

private:
	ordered_json js_content;
	std::stringstream msg_ss;
};

int main(int argc, char* argv[]) {
	ordered_json js_content;
	js_content["name"] = "ZhangSan";
	js_content["sex"] = "Man";
	js_content["age"] = 18;

	message_serializer ser(js_content);
	person p;
	ser >> p;
	
	ser << p;
	std::cout << ser.str() << std::endl;

	js_content["name"] = "Lily";
	js_content["sex"] = "Woman";
	js_content["age"] = 20;
 	ser.json(js_content);
	ser.str("");
	ser >> p;
	ser << p;
	std::cout << ser.str() << std::endl;


	ordered_json js_staff;
	js_staff["name"] = "LyYuan";
	js_staff["salary"] = 50000;
	ser.json(js_staff);
	ser << "\n";
	staff st;
	ser >>  st;
	ser << st;
	std::cout << ser.str() << std::endl;



    return EXIT_SUCCESS;
}
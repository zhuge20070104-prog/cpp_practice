#ifndef _FREDRIC_CONTACT_H_
#define _FREDRIC_CONTACT_H_

#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <initializer_list>


enum class Group {
    Friend,
    Family,
    Coworker,
    Acquaintance    
};

std::ostream& operator<<(std::ostream& os, Group const& group); 

enum class SortMethod {
    FirstName,
    LastName
};

enum class FilterType {
    Company, 
    Grouped,
    FirstName,
    LastName
};

enum class CountType {
    Company,
    Group
};

enum class PrintMethod {
    All,
    FirstNameWithPrimaryNumber
};

struct Contact {
    std::string first_name;
    std::string last_name;
    std::string primary_number;
    std::string secondary_number;
    std::string email;
    std::string address;
    std::string company;
    Group group;

    friend std::ostream& operator<<(std::ostream& os, Contact const& contact);
};


class ContactManager {
public:
    static void add_contacts(std::initializer_list<Contact> const& contacts);
    static void add_contact(Contact const& contact);
    static void sort_by_name(SortMethod method);
    static void print_primary_number();
    static void print(std::vector<Contact> const& cons, PrintMethod method);
    static void filter_and_print(FilterType type, std::string filter_str);
    static void group_count(CountType count_type);
private:
    static std::vector<Contact> contacts;
    static std::unordered_map<std::string, std::vector<Contact>> company_map;
    static std::unordered_map<Group, std::vector<Contact>> group_map;
};

#endif
#include "contact.h"
#include <algorithm>

std::vector<Contact> ContactManager::contacts {};
std::unordered_map<std::string, std::vector<Contact>> ContactManager::company_map{};
std::unordered_map<Group, std::vector<Contact>> ContactManager::group_map{};


void  ContactManager::add_contacts(std::initializer_list<Contact> const& contacts) {
    for(auto const& contact: contacts) {
        ContactManager::add_contact(contact);
    }
}

 void ContactManager::add_contact(Contact const& contact) {
    contacts.push_back(contact);
    company_map[contact.company].push_back(contact);
    group_map[contact.group].push_back(contact);
 }

void ContactManager::sort_by_name(SortMethod method) {
    std::sort(contacts.begin(), contacts.end(), [method](Contact const& left, Contact const& right) {
        if(method == SortMethod::FirstName) {
            return left.first_name < right.first_name;
        } else {
            return left.last_name < right.last_name;
        }
    });

    std::cout << "Sort By Name result:" << std::endl;
    ContactManager::print(contacts, PrintMethod::All);
}

void ContactManager::print_primary_number() {
    ContactManager::print(contacts, PrintMethod::FirstNameWithPrimaryNumber);
}

void ContactManager::print(std::vector<Contact> const& cons, PrintMethod method) {
    for(auto const& contact: cons) {
        if(method == PrintMethod::All) {
            std::cout << contact << std::endl;
        } else {
            std::cout << contact.first_name << ": " << contact.primary_number << std::endl; 
        }
    }
}


struct ContactFilter {
    std::vector<Contact> results;

    ContactFilter(FilterType type_, std::string const& filter_str_): type(type_), filter_str(filter_str_) {

    }

    void operator()(Contact const& contact)  {
        if(type == FilterType::Company) {
            if(contact.company == filter_str) {
                results.push_back(contact);
            } 
        } else if(type == FilterType::FirstName) {
            if(contact.first_name == filter_str) {
                results.push_back(contact);
            }
        } else if(type == FilterType::LastName) {
            if(contact.last_name == filter_str) {
                results.push_back(contact);
            }
        }
    }

    FilterType type;
    std::string filter_str;
};

void ContactManager::filter_and_print(FilterType type, std::string filter_str) {
    if(type != FilterType::Grouped) {
        ContactFilter c_filter(type, filter_str);
        c_filter = std::for_each(contacts.begin(), contacts.end(), c_filter);
        ContactManager::print(c_filter.results, PrintMethod::All);
        return;
    }

    // Handle Group print
    for(auto const& group_contact: group_map) {
        std::cout << group_contact.first << std::endl;
        ContactManager::print(group_contact.second, PrintMethod::All); 
    }
}

void ContactManager::group_count(CountType count_type) {
    if(count_type == CountType::Company) {
        for(auto const& company_contact: company_map) {
            std::cout << company_contact.first << ": ";
            std::cout << company_contact.second.size() << std::endl;
        }
        return;
    }

    for(auto const& group_contact: group_map) {
        std::cout << group_contact.first << ": ";
        std::cout << group_contact.second.size() << std::endl;
    }
}

std::ostream& operator<<(std::ostream& os, Group const& group) {
    auto g_num = (int)group;
    switch(g_num) {
        case 0:
            os << "Friend";
            break;
        case 1:
            os << "Family";
            break;
        case 2:
            os << "Coworker";
            break;
        case 3:
            os << "Acquaintance";
            break;
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, Contact const& contact) {
    os <<  contact.first_name << " --> " << contact.last_name << " --> " << contact.company <<
        " --> " << contact.address << " --> " << contact.email << " --> " 
        << (int)contact.group << " --> " << contact.primary_number << " --> "
        << contact.secondary_number << std::endl;
    return os; 
}
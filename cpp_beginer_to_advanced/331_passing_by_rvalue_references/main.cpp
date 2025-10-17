#include <exception>
#include <iostream>
#include <string>
#include <string_view>

class Item {
    friend std::ostream& operator<<(std::ostream& os, const Item& item);
public:
    Item(): m_data {new int} {}
    explicit Item(int value): m_data {new int(value)} {}
    Item(const Item& src): m_data {new int} {
        std::cout << "Copy constructor called" << std::endl;
        *m_data = *src.m_data;
    }

    Item& operator=(const Item& src) {
        std::cout << "Copy assignment operator called" << std::endl;
        if(this == &src) {
            return *this;
        }

        *m_data = *src.m_data;
        return *this;
    }

    Item(Item&& src) noexcept {
        std::cout << "Move constructor called" << std::endl;
        m_data = src.m_data;
        src.m_data = nullptr;
    }

    Item& operator=(Item&& src) noexcept {
        std::cout << "Move assignment operator called" << std::endl;
        if(this == &src) {
            return *this;
        }

        m_data = src.m_data;
        src.m_data = nullptr;
        return *this;
    }

    ~Item() {
        std::cout << "Destructor called" << std::endl;
        delete m_data;
    }

private:
    int* m_data {nullptr};
};

std::ostream& operator<<(std::ostream& os, const Item& item) {
    os << "Item: " << *item.m_data;
    return os;
}

Item get_value() {
    return Item(21);
}

void do_something(Item&& item) {
    Item local_item = item;
}

int main(int argc, char* argv[]) {
    
    Item&& rvalue_item {get_value()};

    Item item1;

    // though rvalue_item is a rvalue, it is treated as lvalue
    // because it has a name : rvalue_item
    // lvalue by default calls the copy ctor/assign.
    item1 = rvalue_item;

    item1 = std::move(rvalue_item);

    do_something(std::move(item1));
    return EXIT_SUCCESS;
}

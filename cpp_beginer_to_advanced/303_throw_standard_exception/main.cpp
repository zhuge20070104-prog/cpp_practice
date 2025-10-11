#include <iostream>
#include <string>
#include <string_view>
#include <exception>


class Students {
public:
    Students(std::string_view s1, std::string_view s2, std::string_view s3, std::string_view s4, std::string_view s5) {
        m_names[0] = s1;
        m_names[1] = s2;
        m_names[2] = s3;
        m_names[3] = s4;
        m_names[4] = s5;
    }
    ~Students() = default;

    std::string& get_student(std::size_t index) {
        const std::string message {"Index out of range, valid range: 0-4"};
        if(index < 0 || index > 4) {
            throw std::out_of_range(message);
        }
        return m_names[index];
    }
private:
    std::string m_names[5] {};
};


int main(int argc, char* argv[]) {
    Students students {"John", "Jane", "Jim", "Jill", "Jack"};

    std::cout << students.get_student(4) << std::endl;

    try {
        std::cout << students.get_student(-2) << std::endl;
    }catch(std::exception& ex) {
        std::cout << "Something is wrong: " << ex.what() << std::endl;
    }
    return EXIT_SUCCESS;
}
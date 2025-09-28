#ifndef _FREDRIC_SCORES_H_
#define _FREDRIC_SCORES_H_

#include <iostream>
#include <string>

class Scores {
public:
    Scores() = delete;
    explicit Scores(const std::string& course_name): 
        m_course_name{course_name} {

    }

    double& operator[](std::size_t index);
    const double& operator[](std::size_t index) const;

    void print_info() const;

private:
    std::string m_course_name;
    double m_score[20]{};
};

#endif
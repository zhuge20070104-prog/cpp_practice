#include "scores.h"
#include <cassert>

void Scores::print_info() const {
    std::cout << m_course_name << ": [";

    for(std::size_t i{0}; i<20; ++i) {
        std::cout << m_score[i] << " ";
    }

    std::cout << "]\n";
}


double& Scores::operator[](std::size_t index) {
    assert((index>=0) && (index<20));
    return m_score[index];
}

const double& Scores::operator[](std::size_t index) const {
    assert((index>=0) && (index<20));
    return m_score[index];
}
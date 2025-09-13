#ifndef _FREDRIC_PRINTER_H_
#define _FREDRIC_PRINTER_H_

#include <algorithm> 

template<typename container_t>
class printer_t {
public:
printer_t(container_t const& container):
    m_container(container) {
}

void operator()() {
    std::cout << "Start to print out container: " << std::endl;
    std::for_each(m_container.begin(), m_container.end(), [](auto const& element) {
        std::cout << element << " ";
    });
    std::cout << "===========" << std::endl;
}

private:
    container_t const& m_container;
};

template <typename container_t> 
printer_t<container_t> make_printer(container_t const& container) {
    return printer_t<container_t>(container);
}

#endif
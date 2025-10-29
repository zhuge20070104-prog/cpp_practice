cmake_minimum_required(VERSION 3.5)

project(374_constrained_iterator_pair_algorithms LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(374_constrained_iterator_pair_algorithms main.cpp)


include(GNUInstallDirs)
install(TARGETS 374_constrained_iterator_pair_algorithms
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

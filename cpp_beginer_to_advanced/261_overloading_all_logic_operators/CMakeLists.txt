cmake_minimum_required(VERSION 3.5)

project(261_overloading_all_logic_operators LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(261_overloading_all_logic_operators main.cpp
                point.cpp)


include(GNUInstallDirs)
install(TARGETS 261_overloading_all_logic_operators
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

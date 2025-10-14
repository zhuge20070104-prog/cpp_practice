cmake_minimum_required(VERSION 3.5)

project(321_friends_of_class_templates LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(321_friends_of_class_templates main.cpp)


include(GNUInstallDirs)
install(TARGETS 321_friends_of_class_templates
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

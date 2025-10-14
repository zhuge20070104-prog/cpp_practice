cmake_minimum_required(VERSION 3.5)

project(320_class_member_func_specialization LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(320_class_member_func_specialization main.cpp)


include(GNUInstallDirs)
install(TARGETS 320_class_member_func_specialization
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

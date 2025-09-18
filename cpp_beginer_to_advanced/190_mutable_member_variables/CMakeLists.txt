cmake_minimum_required(VERSION 3.5)

project(190_mutable_member_variables LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(190_mutable_member_variables main.cpp)


include(GNUInstallDirs)
install(TARGETS 190_mutable_member_variables
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

cmake_minimum_required(VERSION 3.5)

project(211_member_variables_of_other_types LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(211_member_variables_of_other_types main.cpp)


include(GNUInstallDirs)
install(TARGETS 211_member_variables_of_other_types
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

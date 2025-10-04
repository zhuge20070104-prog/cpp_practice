cmake_minimum_required(VERSION 3.5)

project(275_resurrection_member_back_in_context LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(275_resurrection_member_back_in_context main.cpp
    person.cpp
    engineer.cpp
    civil_engineer.cpp)


include(GNUInstallDirs)
install(TARGETS 275_resurrection_member_back_in_context
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

cmake_minimum_required(VERSION 3.5)

project(366_all_of_any_of_none_of LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(366_all_of_any_of_none_of main.cpp)


include(GNUInstallDirs)
install(TARGETS 366_all_of_any_of_none_of
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

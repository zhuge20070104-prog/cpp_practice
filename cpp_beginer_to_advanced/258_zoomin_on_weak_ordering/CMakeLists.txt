cmake_minimum_required(VERSION 3.5)

project(258_zoomin_on_weak_ordering LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(258_zoomin_on_weak_ordering main.cpp
             comparable_string.cpp)


include(GNUInstallDirs)
install(TARGETS 258_zoomin_on_weak_ordering
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

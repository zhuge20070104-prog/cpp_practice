cmake_minimum_required(VERSION 3.5)

project(220_anonymous_namespace LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(220_anonymous_namespace main.cpp)


include(GNUInstallDirs)
install(TARGETS 220_anonymous_namespace
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

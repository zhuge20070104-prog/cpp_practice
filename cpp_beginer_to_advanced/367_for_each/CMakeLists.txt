cmake_minimum_required(VERSION 3.5)

project(367_for_each LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(367_for_each main.cpp)


include(GNUInstallDirs)
install(TARGETS 367_for_each
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

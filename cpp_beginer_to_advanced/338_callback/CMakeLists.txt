cmake_minimum_required(VERSION 3.5)

project(338_callback LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(338_callback main.cpp)


include(GNUInstallDirs)
install(TARGETS 338_callback
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

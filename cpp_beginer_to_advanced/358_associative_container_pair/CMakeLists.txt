cmake_minimum_required(VERSION 3.5)

project(358_associative_container_pair LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(358_associative_container_pair main.cpp)


include(GNUInstallDirs)
install(TARGETS 358_associative_container_pair
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

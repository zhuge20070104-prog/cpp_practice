cmake_minimum_required(VERSION 3.5)

project(204_friend_functions LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(204_friend_functions main.cpp)


include(GNUInstallDirs)
install(TARGETS 204_friend_functions
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

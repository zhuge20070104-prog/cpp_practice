cmake_minimum_required(VERSION 3.5)

project(353_sequence_container_deque LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(353_sequence_container_deque main.cpp)


include(GNUInstallDirs)
install(TARGETS 353_sequence_container_deque
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
